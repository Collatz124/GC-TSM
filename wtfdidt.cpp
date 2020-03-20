// WHY THE FUCK DID I DO THIS
void NearestNeighbour (Point* points, short *pathTPS) {
	int pointsConnectedWithPath = 1;
	while (pointsConnectedWithPath < NUMBER_OF_POINTS) {
		// Initialise the edges
		std::vector<Edge> edges;

		// Create the edges
		for (int i = 1; i < NUMBER_OF_POINTS; i++) {
			if (checkIndex(pathTPS, i) == false) {
				// Only create an edge is the node havent been visited
				Edge Temp;
				Temp.len = abs(points[i].x - points[pathTPS[pointsConnectedWithPath - 1]].x) + abs(points[i].y - points[pathTPS[pointsConnectedWithPath - 1]].y);
				Temp.toPointIndexed = (short) i;
				edges.push_back(Temp);
			} 
		}

		// Find the point closes by
		std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
			return a.len < b.len;
		});

		short index;
		for (int i = 0; i < edges.size(); i++) {
			if (checkIndex(pathTPS, edges[i].toPointIndexed) == false) {
				index = edges[i].toPointIndexed;
				break;
			}
		}
		pathTPS[pointsConnectedWithPath] = index;
		pointsConnectedWithPath++;
	}
}

void NearestNeighbourEdgeMatrix (Point* points, short *pathTPS) {
	// Create a Edge Matrix and comput the cost of each edge
	float edgeMatrix[NUMBER_OF_POINTS][NUMBER_OF_POINTS]; // The first index says what point the the edge is from, the second index specifies what point the edge is to
	for (int i = 0; i < NUMBER_OF_POINTS; i++) {
		for (int j = 0; j < NUMBER_OF_POINTS; j++) {
			if (i != j) {
				edgeMatrix[i][j] = abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y);
			} else {
				edgeMatrix[i][j] = 10000000.0;
			}
		}
	}
	// TODO: Find the bug inside of this function
	int pointsConnectedWithPath = 1;
	while (pointsConnectedWithPath < NUMBER_OF_POINTS) {
		Edge edges[20];

		for (int i = 0; i < NUMBER_OF_POINTS; i++) {
			edges[i].len = edgeMatrix[pathTPS[pointsConnectedWithPath - 1]][i];
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