#include <cstdio>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
using namespace std;

// The state structure has two integer members x and y, which represent the amounts of water in the two jugs, respectively.
//The operator < function is an overloaded less than operator for the state structure. It's used to compare two state objects for ordering.
//The function takes a constant reference to another state object (that) as an argument.
//Inside the function, it first compares the x values of the two states. If they are not equal, it returns true if the x value of the current state (*this) is less than the x value of the other state (that). This ensures that states are ordered based on their x values.
//If the x values are equal, it proceeds to compare the y values. If they are not equal, it returns true if the y value of the current state is less than the y value of the other state. This ensures that states with the same x values are further ordered based on their y values.
//The function returns false if both the x and y values of the current state are equal to the corresponding values of the other state.
//The that keyword is used here as a reference to the other state object being compared to the current state. It's a conventional name often used to refer to the right-hand side of a comparison operation. In this context, that represents the other state object against which the current state object is being compared.


// Representation of a state (x, y)
// x and y are the amounts of water in litres in the two jugs respectively
struct state {
    int x, y;

    // Used by map to efficiently implement lookup of seen states
    bool operator < (const state& that) const {
        if (x != that.x) return x < that.x;
        return y < that.y;
    }
};

// Capacities of the two jugs respectively and the target amount
int capacity_x, capacity_y, target = 2;

void bfs(state start, stack <pair <state, int> >& path)   {
    //start: Represents the initial state of the water jugs.
    //path: Represents a stack used to store the path from the initial state to the goal state.
    queue <state> s; // This queue will be used for implementing the breadth-first search algorithm.
    state goal = (state) {-1, -1};//This variable will store the goal state, i.e., the state where the desired amount of water is present in one of the jugs. Here, it's initialized with -1 for both x and y to indicate that the goal state hasn't been found yet.

    map <state, pair <state, int> > parentOf; // maps a state to its parent state and the action taken to reach it. This map is used to track the path back from the goal state to the initial state.

    s.push(start);// Enqueues the initial state start into the queue s.
    parentOf[start] = make_pair(start, 0); // Initializes the parentOf map such that the parent of the start state is itself, and the action taken to reach it is 0. This signifies that start has no parent as it's the starting state, and no action has been taken to reach it.

    while (!s.empty())    {
        // Get the state at the front of the queue
        state top = s.front();
        s.pop();

        // If the target state has been found, break
        if (top.y == target) {
            goal = top;
            break;
        }

        // Find the successors of this state
        // This step uses production rules to produce successors of the current state
        // while pruning away branches which have been seen before

        // Rule 1: (x, y) -> (capacity_x, y) if x < capacity_x
        // Fill the first jug
        if (top.x < capacity_x)  {
            state child = (state) {capacity_x, top.y};
            // Consider this state for visiting only if it has not been visited before
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 1);
            }
        }

        // Rule 2: (x, y) -> (x, capacity_y) if y < capacity_y
        // Fill the second jug
        if (top.y < capacity_y)  {
            state child = (state) {top.x, capacity_y};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 2);
            }
        }
        //In this rule, the action is to empty the first jug, which corresponds to setting the amount of water in the first jug to 0 while keeping the amount of water in the second jug unchanged.
        //After creating the child state child, the code checks if this state has not been visited before (i.e., it's not present in the parentOf map).
        //If the child state is indeed new, it's enqueued into the queue s for further exploration.
        //Finally, the action taken to reach this child state is recorded in the parentOf map. Here, 3 signifies that the action is to empty the first jug. The number 3 serves as a code to represent this particular action, allowing the program to later identify and describe the actions taken along the path from the initial state to the goal state.

        // Rule 3: (x, y) -> (0, y) if x > 0
        // Empty the first jug
        if (top.x > 0)  {
            state child = (state) {0, top.y};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 3);
            }
        }

        // Rule 4: (x, y) -> (x, 0) if y > 0
        // Empty the second jug
        if (top.y > 0)  {
            state child = (state) {top.x, 0};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 4);
            }
        }

        // Rule 5: (x, y) -> (min(x + y, capacity_x), max(0, x + y - capacity_x)) if y > 0
        // Pour water from the second jug into the first jug until the first jug is full
        // or the second jug is empty
        if (top.y > 0)  {
            state child = (state) {min(top.x + top.y, capacity_x), max(0, top.x + top.y - capacity_x)};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 5);
            }
        }

        // Rule 6: (x, y) -> (max(0, x + y - capacity_y), min(x + y, capacity_y)) if x > 0
        // Pour water from the first jug into the second jug until the second jug is full
        // or the first jug is empty
        if (top.x > 0)  {
            state child = (state) {max(0, top.x + top.y - capacity_y), min(top.x + top.y, capacity_y)};
            if (parentOf.find(child) == parentOf.end()) {
                s.push(child);
                parentOf[child] = make_pair(top, 6);
            }
        }
    }

    // Target state was not found
    if (goal.x == -1 || goal.y == -1)
        return; //After the breadth-first search is complete, this conditional statement checks whether the goal state has been found.
        //If either the x or y value of the goal state remains -1, it indicates that the target state has not been reached.
        //In this case, the function returns without further processing.

    // backtrack to generate the path through the state space
    path.push(make_pair(goal, 0));
    // remember parentOf[start] = (start, 0)
    while (parentOf[path.top().first].second != 0)
        path.push(parentOf[path.top().first]);

        //The function enters a while loop to backtrack through the parentOf map and construct the path.
        //It repeatedly pushes states onto the path stack until it reaches the initial state (start), which is identified by the action value of 0 in the pair stored in the parentOf map.
        //During each iteration of the loop, it accesses the top state of the path stack and retrieves its parent state from the parentOf map.
        //The loop continues until the action value of the parent state becomes 0, indicating that it's the initial state.
        //At this point, the loop stops, and the path stack contains the sequence of states representing the path from the initial state to the goal state, including both states and the actions taken to reach each state.
}

int main()  {
    stack <pair <state, int> > path; // Initializes an empty stack named path. This stack will be used to store pairs consisting of a state (state struct) and an integer representing the action taken to reach that state.

    printf("Enter the capacities of the two jugs : ");
    scanf("%d %d", &capacity_x, &capacity_y);

    bfs((state) {0, 0}, path);
    if (path.empty())
        printf("\nTarget cannot be reached.\n");
    else    {
        printf("\nNumber of moves to reach the target : %ld\nOne path to the target is as follows :\n", path.size() - 1);
        while (!path.empty())   {
            state top = path.top().first;
            int rule = path.top().second;
            path.pop();

            switch (rule)   {
                case 0: printf("State : (%d, %d)\n#\n", top.x, top.y);
                        break;
                case 1: printf("State : (%d, %d)\nAction : Fill the first jug\n", top.x, top.y);
                        break;
                case 2: printf("State : (%d, %d)\nAction : Fill the second jug\n", top.x, top.y);
                        break;
                case 3: printf("State : (%d, %d)\nAction : Empty the first jug\n", top.x, top.y);
                        break;
                case 4: printf("State : (%d, %d)\nAction : Empty the second jug\n", top.x, top.y);
                        break;
                case 5: printf("State : (%d, %d)\nAction : Pour from second jug into first jug\n", top.x, top.y);
                        break;
                case 6: printf("State : (%d, %d)\nAction : Pour from first jug into second jug\n", top.x, top.y);
                        break;
            }
        }
    }

    return 0;
}