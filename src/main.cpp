#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <math.h>
#include <algorithm>
#include <chrono>

#define NUMBER_OF_POINTS 20

typedef struct {
	float x, y;
} Point;

bool isDigit(char chr) {
	// Simpely returns true if chr is a digit else it returns false
	if ((int(chr) > 48) && (int(chr) < 57)) {
		return true;
	}
	return false;
}

float convertStrToFloatNumber (std::string n) {
	// Converts the number n to a float in the form of 000.000
	while(n.length() < 6) {
		n = "0" + n;
	}
	// Insert . at the 3. spot
	n.insert(3, ".");
	return strtof((n).c_str(), 0);
}

std::string readStringFromFile (std::string fileName) {
	// Reads the data from a txt file
	if (fileName != "") {
		std::ifstream inFile;
		inFile.open(fileName + ".txt");
		if (!inFile) {
			std::cout << "unaple to open file named: " << fileName << std::endl; 
			exit(1);
		}
		std::string str((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		inFile.close();
		return str;
	} else {
		return "";
	}
}

void parse (Point *points, std::string input) {
	// This function parses the input string and creates a list of numbers.
	float currentPoint[2] = {0.0, 0.0};
	int numberOfPoints = 0;
	int i = 0;
	bool x = false, y = false;
	std::string str;
	while (i < input.length()) {
		if (input[i] == 'X') {
			x = true;
			i++;
			while (input[i + 1] != 'Y') {
				str.append(1, input[i]);
				i++;
			}
			str.append(1, input[i]);
			currentPoint[0] = convertStrToFloatNumber(str);
			str = "";
		} else if (input[i] == 'Y') {
			y = true;
			i++;
			while (input[i + 1] != '\n') {
				str.append(1, input[i]);
				i++;
			}
			str.append(1, input[i]);
			currentPoint[1] = convertStrToFloatNumber(str);
			str = "";
		} 
		if (x == true && y == true) {
			points[numberOfPoints] = {currentPoint[0], currentPoint[1]};
			numberOfPoints++;
			currentPoint[0] = 0.0;
			currentPoint[1] = 0.0;
			x = false;
			y = false;
		}
		i++;
	}
}

typedef struct {
	float len;
	short toPointIndexed;
} Edge;

bool checkIndex (short *pathTPS, short index) {
	// checks if the index has already been picked (is a part of the pathTPS array)
	for (int i = 0; i < NUMBER_OF_POINTS - 1; i++) {
		if (pathTPS[i] == index) {
			return true;
		}
	} 
	return false;
}

void NearestNeighboorArrayVersion (Point* points, short *pathTPS) {
	int pointsConnectedWithPath = 1;
	Edge edges[20];
	while (pointsConnectedWithPath < NUMBER_OF_POINTS) {
		for (int i = 0; i < NUMBER_OF_POINTS; i++) {
			if (checkIndex(pathTPS, (short) i) == false) {
				edges[i].len =  abs(points[i].x - points[pathTPS[pointsConnectedWithPath-1]].x) + abs(points[i].y - points[pathTPS[pointsConnectedWithPath-1]].y);
			} else {
				edges[i].len = 1000000.0;
			}
			edges[i].toPointIndexed = (short) i;
		}

		// Find the point closes by
		std::sort(edges, edges + NUMBER_OF_POINTS, [](Edge a, Edge b) {
			return a.len < b.len;
		});

		short index = 0;
		for (int i = 0; i < NUMBER_OF_POINTS; i++) {
			if (checkIndex(pathTPS, edges[i].toPointIndexed) == false) {
				index = edges[i].toPointIndexed;
				break;
			}
		}
		pathTPS[pointsConnectedWithPath] = index;
		pointsConnectedWithPath++;
	}
}

float getLenOfPath (Point *points, short * pathTPS) {
	float sum = 0.0;
	for (int i = 0; i < NUMBER_OF_POINTS - 1; i++) {
		short index = pathTPS[i];
		if (pathTPS[i] == 0) {
			sum += sqrtf(pow(points[0].x, 2.0) + pow(points[0].y, 2.0));
		} else {
			sum += sqrtf(pow(points[index].x - points[pathTPS[i] - 1].x, 2.0) + pow(points[index].y - points[pathTPS[i] - 1].y, 2.0));
		}
	}
	return sum;
}

void printPath (Point *points, short * pathTPS) {
	std::cout << "final path: " << std::endl;
	std::cout << "x: ";
	for (int i = 0; i < NUMBER_OF_POINTS; i++) {
		std::cout << points[pathTPS[i]].x << ", ";
	}
	std::cout << std::endl << "y: "; 
	for (int i = 0; i < NUMBER_OF_POINTS; i++) {
		std::cout << points[pathTPS[i]].y << ", ";
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	// Load points from file:
	std::string str = readStringFromFile(argv[1]);
	Point points[NUMBER_OF_POINTS];
	// Initialize the points
	for (int i = 0; i < NUMBER_OF_POINTS; i++) {
		points[i].x = 0.0;
		points[i].y = 0.0;
	}
	parse(points, str);
	std::sort(points, points + NUMBER_OF_POINTS, [](Point p1, Point p2) {
		return p1.y < p2.y;
	});
	std::cout << "\nPoints after parsing " << std::endl;
	for (int i = 0; i < NUMBER_OF_POINTS; i++) {
		std::cout << points[i].x << ", " << points[i].y << std::endl;
	} 
	// Find the fastes pathTPS betwen the points and sort them by this pathTPS:
	short pathTPS[NUMBER_OF_POINTS];
	pathTPS[0] = 0;
	// Vector version
	// Array version
	auto start = std::chrono::high_resolution_clock::now();
	NearestNeighboorArrayVersion(points, pathTPS);
	std::cout << "Length of nearest neighboor: " << getLenOfPath(points, pathTPS) << " mm" << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Nearest neightboor array version: " << elapsed.count() << std::endl;
	printPath(points, pathTPS);
	return 0;
}