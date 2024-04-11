#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <cmath>
#include <functional> // Include functional for std::function

using namespace std;

// Define a structure to represent a cell in the grid
struct Cell {
    int x, y; // Coordinates of the cell
    int f, g, h; // A* parameters
    Cell* parent; // Pointer to the parent cell
};

// Function to calculate the Manhattan distance heuristic
int heuristic(Cell* a, Cell* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

// Function to check if a cell is within the grid and is traversable
bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& grid) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0);
}

// Function to implement A* search algorithm
vector<Cell*> astar(vector<vector<int>>& grid, Cell* start, Cell* end) {
    // Define directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
    
    int rows = grid.size();
    int cols = grid[0].size();
    
    // Create a priority queue for open cells
    priority_queue<Cell*, vector<Cell*>, function<bool(Cell*, Cell*)>> openList([](Cell* a, Cell* b) { return a->f > b->f; });
    
    // Initialize start cell parameters
    start->g = 0;
    start->h = heuristic(start, end);
    start->f = start->g + start->h;
    openList.push(start);
    
    // Create a 2D vector to track visited cells
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    visited[start->x][start->y] = true;
    
    // A* search algorithm
    while (!openList.empty()) {
        Cell* current = openList.top();
        openList.pop();
        
        // Check if the current cell is the destination
        if (current->x == end->x && current->y == end->y) {
            vector<Cell*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        
        // Explore neighbors
        for (int i = 0; i < 8; ++i) {
            int nextX = current->x + dx[i];
            int nextY = current->y + dy[i];
            
            // Check if the neighbor is valid
            if (isValid(nextX, nextY, rows, cols, grid) && !visited[nextX][nextY]) {
                Cell* neighbor = new Cell();
                neighbor->x = nextX;
                neighbor->y = nextY;
                neighbor->parent = current;
                neighbor->g = current->g + 1; // Assuming each move has a cost of 1
                neighbor->h = heuristic(neighbor, end);
                neighbor->f = neighbor->g + neighbor->h;
                openList.push(neighbor);
                visited[nextX][nextY] = true;
            }
        }
    }
    
    // No path found
    return {};
}

int main() {
    int rows, cols;
    
    // Get user input for grid dimensions
    cout << "Enter number of rows and columns: ";
    cin >> rows >> cols;
    
    // Initialize grid with dimensions provided by user
    vector<vector<int>> grid(rows, vector<int>(cols));
    
    // Get user input for grid
    cout << "Enter grid (0 for traversable, 1 for obstacle):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> grid[i][j];
        }
    }
    
    // Get user input for start and end points
    int startX, startY, endX, endY;
    cout << "Enter start point (row column): ";
    cin >> startX >> startY;
    
    cout << "Enter end point (row column): ";
    cin >> endX >> endY;
    
    // Define start and end cells
    Cell* start = new Cell();
    start->x = startX;
    start->y = startY;
    
    Cell* end = new Cell();
    end->x = endX;
    end->y = endY;
    
    // Perform A* search
    vector<Cell*> path = astar(grid, start, end);
    
    // Output the path
    if (path.empty()) {
        cout << "No path found." << endl;
    } else {
        cout << "Path found:" << endl;
        for (auto cell : path) {
            cout << "(" << cell->x << ", " << cell->y << ")" << endl;
        }
    }
    
    return 0;
}
