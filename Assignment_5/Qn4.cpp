#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Define travel times for each family member
    vector<int> travelTimes = {1, 3, 6, 8, 12};

    // Initialize variables to track time and family members on each side of the river
    int timeElapsed = 0;
    vector<int> leftBank = travelTimes;
    vector<int> rightBank;

    // Output initial configuration
    cout << "Initial configuration:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    // Cross 1-second and 3-second members together
    timeElapsed += 3;
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 1));
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 3));
    rightBank.push_back(1);
    rightBank.push_back(3);

    // Output configuration after crossing
    cout << "\nAfter crossing 1-second and 3-second members:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    // Send 1-second member back
    timeElapsed += 1;
    leftBank.push_back(1);
    rightBank.erase(find(rightBank.begin(), rightBank.end(), 1));

    // Output configuration after sending 1-second member back
    cout << "\nAfter sending 1-second member back:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    // Cross 8-second and 12-second members together
    timeElapsed += 12;
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 8));
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 12));
    rightBank.push_back(8);
    rightBank.push_back(12);

    // Output configuration after crossing 8-second and 12-second members
    cout << "\nAfter crossing 8-second and 12-second members:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    // Send 3-second member back
    timeElapsed += 3;
    leftBank.push_back(3);
    rightBank.erase(find(rightBank.begin(), rightBank.end(), 3));

    // Output configuration after sending 3-second member back
    cout << "\nAfter sending 3-second member back:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    // Cross 1-second and 6-second members together
    timeElapsed += 6;
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 1));
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 6));
    rightBank.push_back(1);
    rightBank.push_back(6);

    // Output configuration after crossing 1-second and 6-second members
    cout << "\nAfter crossing 1-second and 6-second members:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    // Send 1-second member back
    timeElapsed += 1;
    leftBank.push_back(1);
    rightBank.erase(find(rightBank.begin(), rightBank.end(), 1));

    // Output configuration after sending 1-second member back
    cout << "\nAfter sending 1-second member back:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    // Cross 1-second and 3-second members together again
    timeElapsed += 3;
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 1));
    leftBank.erase(find(leftBank.begin(), leftBank.end(), 3));
    rightBank.push_back(1);
    rightBank.push_back(3);

    // Output final configuration
    cout << "\nFinal configuration:\n";
    cout << "Time: " << timeElapsed << "s, Left bank: ";
    for (const auto& person : leftBank) {
        cout << person << " ";
    }
    cout << ", Right bank: ";
    for (const auto& person : rightBank) {
        cout << person << " ";
    }
    cout << endl;

    return 0;
}
