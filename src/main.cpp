#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>

#define NUMBER_OF_POINTS 20;

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
	if (6 - n.length() > 0) {
		// The representation is with trailing zeros
		n.append(6 - n.length(), '0');
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
			str.append(1, '0');
			while (input[i + 1] != 'Y') {
				str.append(1, input[i]);
				i++;
			}
			str.append(1, input[i]);
			std::cout << str << std::endl;
			currentPoint[0] = convertStrToFloatNumber(str);
			str = "";
		} else if (input[i] == 'Y') {
			y = true;
			i++;
			str.append(1, '0');
			while (input[i] != '\n') {
				str.append(1, input[i]);
				i++;
			}
			str.append(1, input[i]);
			std::cout << str << std::endl;
			currentPoint[1] = convertStrToFloatNumber(str);
			str = "";
			std::cout << currentPoint[1] << std::endl;
		} 
		if (x == true && y == true) {
			*(points + sizeof(Point) * numberOfPoints) = {currentPoint[0], currentPoint[1]};
			numberOfPoints++;
			currentPoint[0] = 0.0;
			currentPoint[1] = 0.0;
		}
		i++;
	}
}

int main(int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		std::cout << isDigit(argv[i][0]) << std::endl;
	}
	std::string str = readStringFromFile(argv[1]);
	std::cout << str << std::endl;
	Point points[20] = {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, 
						{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, 
						{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, 
						{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}};
	parse(points, str);
	std::cout << "Points after parsing " << std::endl;
	for (int i = 0; i < (sizeof(points) / (sizeof (float) * 2)); i++) {
		std::cout << points[i].x << ", " << points[i].y << std::endl;
	}
	
	return 0;
}