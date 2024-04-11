#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct State {
    int missionariesLeft;
    int cannibalsLeft;
    int missionariesRight;
    int cannibalsRight;
    bool boatLeft; // true if boat is on the left bank, false if on the right bank
};

bool isValid(int missionaries, int cannibals) {
    if (missionaries < 0 || cannibals < 0)
        return false;
    if (missionaries == 0 || missionaries >= cannibals)
        return true;
    return false;
}

bool isFinalState(const State& state) {
    return state.missionariesLeft == 0 && state.cannibalsLeft == 0;
}

bool operator<(const State& lhs, const State& rhs) {
    return tie(lhs.missionariesLeft, lhs.cannibalsLeft, lhs.missionariesRight, lhs.cannibalsRight, lhs.boatLeft) <
           tie(rhs.missionariesLeft, rhs.cannibalsLeft, rhs.missionariesRight, rhs.cannibalsRight, rhs.boatLeft);
}

vector<State> getPossibleNextStates(const State& currentState) {
    vector<State> possibleNextStates;
    int missionaries[] = {1, 2, 0};
    int cannibals[] = {1, 0, 2};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (missionaries[i] + cannibals[j] <= 2 && (missionaries[i] + cannibals[j]) > 0) {
                State nextState = currentState;
                if (nextState.boatLeft) {
                    nextState.missionariesLeft -= missionaries[i];
                    nextState.cannibalsLeft -= cannibals[j];
                    nextState.missionariesRight += missionaries[i];
                    nextState.cannibalsRight += cannibals[j];
                } else {
                    nextState.missionariesLeft += missionaries[i];
                    nextState.cannibalsLeft += cannibals[j];
                    nextState.missionariesRight -= missionaries[i];
                    nextState.cannibalsRight -= cannibals[j];
                }
                nextState.boatLeft = !currentState.boatLeft;
                if (isValid(nextState.missionariesLeft, nextState.cannibalsLeft) &&
                    isValid(nextState.missionariesRight, nextState.cannibalsRight)) {
                    possibleNextStates.push_back(nextState);
                }
            }
        }
    }
    return possibleNextStates;
}

void printSolution(const vector<State>& solution) {
    for (const auto& state : solution) {
        cout << "(" << state.missionariesLeft << "," << state.cannibalsLeft << ") ";
        if (state.boatLeft)
            cout << "<-- ";
        else
            cout << "--> ";
        cout << "(" << state.missionariesRight << "," << state.cannibalsRight << ")" << endl;
    }
}

vector<State> solveMissionariesAndCannibals() {
    queue<vector<State>> q;
    set<State> visited;
    State initialState = {3, 3, 0, 0, true};
    q.push({initialState});

    while (!q.empty()) {
        vector<State> currentSolution = q.front();
        q.pop();
        State currentState = currentSolution.back();

        if (isFinalState(currentState))
            return currentSolution;

        vector<State> possibleNextStates = getPossibleNextStates(currentState);

        for (const auto& nextState : possibleNextStates) {
            if (visited.find(nextState) == visited.end()) {
                vector<State> nextSolution = currentSolution;
                nextSolution.push_back(nextState);
                q.push(nextSolution);
                visited.insert(nextState);
            }
        }
    }
    return {}; // No solution found
}

int main() {
    vector<State> solution = solveMissionariesAndCannibals();
    if (solution.empty()) {
        cout << "No solution found." << endl;
    } else {
        cout << "Solution:" << endl;
        printSolution(solution);
    }
    return 0;
}
