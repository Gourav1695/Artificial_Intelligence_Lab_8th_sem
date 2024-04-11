#include <bits/stdc++.h>
using namespace std;
#define V 4

// implementation of traveling Salesman Problem
int travllingSalesmanProblem(int graph[][V], int s, vector<int>& path)
{
	// store all vertex apart from source vertex
	vector<int> vertex;
	for (int i = 0; i < V; i++)
		if (i != s)
			vertex.push_back(i);

	// store minimum weight Hamiltonian Cycle.
	int min_path = INT_MAX;
	do {

		// store current Path weight(cost)
		int current_pathweight = 0;

		// compute current path weight
		// Inside the loop, it calculates the total weight (cost) of the current permutation of vertices.
		//k is initialized with the source vertex s. Then, for each vertex in the permutation, it adds the weight of the edge between k and the current vertex (vertex[i]) to current_pathweight. Finally, it adds the weight of the edge from the last vertex back to the source vertex.
		int k = s;
		for (int i = 0; i < vertex.size(); i++) {
			current_pathweight += graph[k][vertex[i]];
			k = vertex[i];
		}
		current_pathweight += graph[k][s];

		// update minimum
		//Updates min_path if the current path weight is smaller than the previously found minimum.
		//Updates path to store the current optimal path.
		//The path includes the starting vertex s, followed by all vertices in the permutation, and then back to s.
		if (current_pathweight < min_path) {
			min_path = current_pathweight;
			path = { s };  // path is a vector of integers, and { s } represents an initializer list with a single element, s. This syntax is used to initialize the vector path with a single element, which is the starting vertex s.
			for (int i : vertex)
				path.push_back(i);
			path.push_back(s);
		}

	} while (
		// This loop continues until all permutations of vertices have been considered.
        //next_permutation generates the next lexicographically greater permutation of the sequence vertex.
		next_permutation(vertex.begin(), vertex.end()));

	return min_path;
}

// Function to calculate the total distance of a path given an adjacency matrix
int calculateTotalDistance(const int adjacencyMatrix[][4], const int path[], int numCities) {
    int totalDistance = 0;
	//This loop iterates over the vertices in the path, from the first vertex to the second-to-last vertex.
	//For each pair of consecutive vertices, it retrieves the weight of the edge between them from the adjacency matrix and adds it to totalDistance.
    for (int i = 0; i < numCities - 1; ++i) {
        totalDistance += adjacencyMatrix[path[i]][path[i + 1]];
    }
    // Add distance back to the starting city
	//After the loop, it adds the distance from the last vertex back to the starting vertex to complete the cycle.
    //It uses path[numCities - 1] to access the last vertex and path[0] to access the starting vertex.
    totalDistance += adjacencyMatrix[path[numCities - 1]][path[0]];
    return totalDistance;
}

//Hill climbing is a local search algorithm used for optimization problems. It starts with an initial solution and iteratively makes small incremental changes to the solution, moving towards a better solution at each step. The algorithm continues until it reaches a peak where no further improvements can be made.

// Function to perform hill climbing to find the shortest path
void hillClimbing(const int adjacencyMatrix[][4], int startingCity, int numCities, int shortestPath[]) {
    int currentPath[numCities];
    for (int i = 0; i < numCities; ++i) {
		// This initialization essentially sets up an initial path where the cities are visited in their natural order, starting from the first city (0) and proceeding sequentially to the last city (numCities - 1). This is a common starting point for many optimization algorithms, including hill climbing, as it provides a simple baseline solution to improve upon.
        currentPath[i] = i; // Initialize the path to 0, 1, 2, ..., n-1
    }

    // Ensure starting city is at index 0
    swap(currentPath[0], currentPath[startingCity]);

    int currentDistance = calculateTotalDistance(adjacencyMatrix, currentPath, numCities);

    while (true) {
        bool improved = false;
        for (int i = 1; i < numCities - 1; ++i) {
            for (int j = i + 1; j < numCities; ++j) {
                // Swap two cities and recalculate distance
                swap(currentPath[i], currentPath[j]);
                int newDistance = calculateTotalDistance(adjacencyMatrix, currentPath, numCities);
                // If the new distance is shorter, keep the swap
                if (newDistance < currentDistance) {
                    currentDistance = newDistance;
                    improved = true;
                    copy(currentPath, currentPath + numCities, shortestPath); // this line of code copies the contents of the currentPath array to the shortestPath array, effectively updating shortestPath to hold the current shortest path found by the hill climbing algorithm
                } else { // Otherwise, revert the swap
                    swap(currentPath[i], currentPath[j]);
                }
            }
        }
        // If no improvement, break the loop
        if (!improved) {
            break;
        }
    }
}

// Driver Code
int main() {
    // matrix representation of graph
    int graph[][V] = { { 0, 10, 15, 20 },
                       { 15, 0, 80, 25 },
                       { 15, 35, 70, 30 },
                       { 20, 25, 3, 0 } };
    int s = 0; // Starting city
    vector<int> path; // Vector to store the optimal path

    // Solve TSP using brute force
    int minCost = travllingSalesmanProblem(graph, s, path);

    // Output the optimal path
    cout << "Optimal Path: ";
    for (int city : path) {
        cout << city + 1 << " "; // Adding 1 to convert 0-based index to 1-based index
    }
    cout << "\nTotal Distance: " << minCost << endl;

    // Solve TSP using hill climbing with the specified starting city
    int shortestPath[V]; // Array to store the shortest path found

    hillClimbing(graph, s, V, shortestPath);

    // Output the shortest path
    cout << "Shortest Path:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << shortestPath[i]+1 << " "; // Adding 1 to convert 0-based index to 1-based index
    }
    cout << s+1; // Outputting the starting city
    cout << endl;

    // Output the total distance of the shortest path
    cout << "Total Distance: " << calculateTotalDistance(graph, shortestPath, V) << endl;

    return 0;
}

