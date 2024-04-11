#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// Define the goal state
vector<vector<int>> goalState = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Define structure for puzzle node
struct PuzzleNode {
    vector<vector<int>> state;
    int heuristic;
    int moves;
    PuzzleNode* parent;

    // Constructor
    PuzzleNode(vector<vector<int>> s, int h, int m, PuzzleNode* p) : state(s), heuristic(h), moves(m), parent(p) {}

    // Compare function for priority queue
    bool operator>(const PuzzleNode& other) const {
        return heuristic + moves > other.heuristic + other.moves;
    }

    // Compare function for set
    bool operator<(const PuzzleNode& other) const {
        return state < other.state;
    }
};

// Function to calculate the heuristic (number of incorrect pieces)
int calculateHeuristic(const vector<vector<int>>& state) {
    int heuristic = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] != goalState[i][j] && state[i][j] != 0) {
                heuristic++;
            }
        }
    }
    return heuristic;
}

// Function to check if a state is the goal state
bool isGoalState(const vector<vector<int>>& state) {
    return state == goalState;
}

// Function to generate possible moves
vector<vector<vector<int>>> generateMoves(const vector<vector<int>>& state) {
    vector<vector<vector<int>>> moves;
    int zeroX, zeroY;

    // Find the position of the empty tile (0)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] == 0) {
                zeroX = i;
                zeroY = j;
                break;
            }
        }
    }

    // Generate moves by swapping empty tile with neighboring tiles
    if (zeroX > 0) {
        vector<vector<int>> newState = state;
        swap(newState[zeroX][zeroY], newState[zeroX - 1][zeroY]);
        moves.push_back(newState);
    }
    if (zeroX < 2) {
        vector<vector<int>> newState = state;
        swap(newState[zeroX][zeroY], newState[zeroX + 1][zeroY]);
        moves.push_back(newState);
    }
    if (zeroY > 0) {
        vector<vector<int>> newState = state;
        swap(newState[zeroX][zeroY], newState[zeroX][zeroY - 1]);
        moves.push_back(newState);
    }
    if (zeroY < 2) {
        vector<vector<int>> newState = state;
        swap(newState[zeroX][zeroY], newState[zeroX][zeroY + 1]);
        moves.push_back(newState);
    }

    return moves;
}

// Function to print the state of the puzzle
void printState(const vector<vector<int>>& state) {
    for (const auto& row : state) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Function to trace back the solution path
void printSolutionPath(PuzzleNode* node) {
    vector<PuzzleNode*> path;
    while (node != nullptr) {
        path.push_back(node);
        node = node->parent;
    }
    reverse(path.begin(), path.end());

    for (PuzzleNode* n : path) {
        printState(n->state);
        cout << endl;
    }
}

// A* algorithm implementation
void solvePuzzle(const vector<vector<int>>& initialState) {
    priority_queue<PuzzleNode*, vector<PuzzleNode*>, greater<PuzzleNode*>> frontier;
    set<vector<vector<int>>> explored;

    PuzzleNode* initialNode = new PuzzleNode(initialState, calculateHeuristic(initialState), 0, nullptr);
    frontier.push(initialNode);

    while (!frontier.empty()) {
        PuzzleNode *currentNode = frontier.top();
        frontier.pop();
        
        if (isGoalState(currentNode->state)) {
            cout << "Solution found in " << currentNode->moves << " moves." << endl;
            printSolutionPath(currentNode);
            return;
        }

        explored.insert(currentNode->state);

        // Generate possible moves
        vector<vector<vector<int>>> possibleMoves = generateMoves(currentNode->state);
        for (const auto& move : possibleMoves) {
            if (explored.find(move) == explored.end()) {
                PuzzleNode* newNode = new PuzzleNode(move, calculateHeuristic(move), currentNode->moves + 1, currentNode);
                frontier.push(newNode);
            }
        }
    }

    cout << "No solution found." << endl;
}

int main() {
    vector<vector<int>> initialState = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    cout << "Enter initial state in the form of a 3x3 matrix.\n";

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cin >> initialState[i][j];
        }
    }
    
    cout << "Enter goal state in the form of a 3x3 matrix.\n";

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cin >> goalState[i][j];
        }
    }

    cout << "Initial state:" << endl;
    printState(initialState);
    cout << endl;

    solvePuzzle(initialState);

    return 0;
}
