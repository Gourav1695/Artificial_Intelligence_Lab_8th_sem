#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
};

class MonkeyBananaProblem {
private:
    int room_width, room_length, ceiling_height, box_height, monkey_height;
    Point gate, window;

public:
    void getUserInputs() {
        cout << "Enter room width: ";
        cin >> room_width;
        cout << "Enter room length: ";
        cin >> room_length;
        cout << "Enter ceiling height: ";
        cin >> ceiling_height;
        cout << "Enter box height: ";
        cin >> box_height;
        cout << "Enter monkey height: ";
        cin >> monkey_height;

        cout << "Enter coordinates of the gate (x y): ";
        cin >> gate.x >> gate.y;

        cout << "Enter coordinates of the window (x y) (summing bottom left corner as 0,0): ";
        cin >> window.x >> window.y;
    }

    bool areCoordinatesValid() {
        return gate.x >= 0 && gate.x <= room_width && gate.y >= 0 && gate.y <= room_length &&
               window.x >= 0 && window.x <= room_width && window.y >= 0 && window.y <= room_length &&
               ceiling_height > 0 && box_height >= 0 && monkey_height >= 0;
    }

    bool canReachBanana() {
       return box_height+monkey_height >= ceiling_height;
    }

    void printStepsToBanana() {
        if (!areCoordinatesValid()) {
            cout << "Invalid coordinates entered. Please enter valid coordinates.\n";
            return;
        }

        if (canReachBanana()) {
            cout << "Steps to reach the banana:\n";
            if (monkey_height >= ceiling_height) {
                cout << "1. Walk towards the center of the room.\n";
                cout << "2. Jump and grab the banana directly.\n";
            } else {
                cout << "1. Walk towards the window.\n";
                cout << "2. Push the box towards the banana.\n";
                cout << "3. Climb onto the box.\n";
                cout << "4. Reach out and grasp the banana.\n";
            }
        } else {
            cout << "The monkey cannot reach the banana.\n";
        }
    }
};

int main() {
    MonkeyBananaProblem problem;
    problem.getUserInputs();
    problem.printStepsToBanana();
    return 0;
}
