#include <bits/stdc++.h>

using namespace std;

struct state {
    int ml, cl, pos, mr, cr;
    state *parent;
    int op;
    bool operator==(const state & rhs) const{
        return ((ml == rhs.ml) && (cl == rhs.cl) && (mr == rhs.mr) && (cr == rhs.cr) && (pos  == rhs.pos));
    }
    // If all these conditions are true for both state objects, it returns true, indicating that the states are equal. Otherwise, it returns false. 
    // This function is crucial for various operations in the code, such as checking if a state has been visited before or if the current state matches the goal state.
};
// This defines a state struct that represents the state of the problem. 
// It contains the number of missionaries and cannibals on the left side of the river (ml and cl), the position of the boat (pos), and the number of missionaries and cannibals on the right side of the river (mr and cr). 
// parent is a pointer to the parent state in the search tree, and op represents the action taken to reach this state. The operator== function is overloaded to compare two states for equality.


// This function calculates the next state given the current state Z and the action j.
// It creates a new state S, copies the values from Z to S, applies the action j to S, and then returns S.
state * nextState(state *Z, const int j) {
  state * S = new state();
  (*S) = (*Z);
  (*S).op  = j;
  switch (j)
  {
    case 0: {  (*S).pos  -= 1; 
               (*S).ml += 0;
               (*S).cl += 1;
               (*S).mr -= 0;
               (*S).cr -= 1;}
            break;
    case 1: {  (*S).pos  -= 1;
               (*S).ml += 0;
               (*S).cl += 2;
               (*S).mr -= 0;
               (*S).cr -= 2;}
            break;  
    case 2: {  (*S).pos  -= 1;
               (*S).ml += 1;
               (*S).cl += 0;
               (*S).mr -= 1;
               (*S).cr -= 0;}
            break;  
    case 3: {  (*S).pos  -= 1;
               (*S).ml += 2;
               (*S).cl += 0;
               (*S).mr -= 2;
               (*S).cr -= 0;}
            break;  
    case 4: {  (*S).pos  -= 1;
               (*S).ml += 1;
               (*S).cl += 1;
               (*S).mr -= 1;
               (*S).cr -= 1;}
            break;  
    case 5: {  (*S).pos  += 1;
               (*S).mr += 0;
               (*S).cr += 1;
               (*S).ml -= 0;
               (*S).cl -= 1;}
            break;  
    case 6: {  (*S).pos  += 1;
               (*S).mr += 0;
               (*S).cr += 2;
               (*S).ml -= 0;
               (*S).cl -= 2;}
            break;  
    case 7: {  (*S).pos  += 1;
               (*S).mr += 1;
               (*S).cr += 0;
               (*S).ml -= 1;
               (*S).cl -= 0;}
            break;              
    case 8: {  (*S).pos  += 1;
               (*S).mr += 2;
               (*S).cr += 0;
               (*S).ml -= 2;
               (*S).cl -= 0;}
            break;                          
    case 9: {  (*S).pos  += 1;
               (*S).mr += 1;
               (*S).cr += 1;
               (*S).ml -= 1;
               (*S).cl -= 1;}
            break;                                      
  }
  // For example, in case 0, the boat moves with one cannibal from the left side to the right side of the river. Therefore, (*S).pos is decremented by 1 (representing the movement of the boat), (*S).cl (number of cannibals on the left) is incremented by 1, and (*S).cr (number of cannibals on the right) is decremented by 1.
  // The other attributes (ml, mr, cl, and cr) remain unchanged as no missionaries are moved.
  return S;
}

bool validState(state *S){
     // Check if the state is valid (all missionaries and cannibals are on one side or the number of missionaries is greater than or equal to the number of cannibals on both sides)
  if(( (*S).cl < 0) || ( (*S).cl > 3)) return false;
  if(( (*S).cr < 0) || ( (*S).cr > 3)) return false;
  if(( (*S).ml < 0) || ( (*S).ml > 3)) return false;
  if(( (*S).mr < 0) || ( (*S).mr > 3)) return false;
  if(( (*S).pos != 0) && ( (*S).pos != 1))  return false;  
  if( (( (*S).cl >  (*S).ml) && ( (*S).ml > 0)) || (( (*S).cr >  (*S).mr) && ( (*S).mr > 0)) ) return false;
  return true;
}

// This function ensures that each state is only visited once during the search process, preventing the algorithm from getting stuck in loops and improving efficiency by avoiding redundant exploration of already visited states.
bool notFound(state *s, vector<state *> &vis){
    // Check if the state is not already visited

    for(int i=0; i<vis.size(); i++){
        if((*s) == (*(vis[i]))) return false;
    }
    return true;
}

void addChildren(queue<state *> &q, state *s, vector<state *> &vis){
    // Add valid children states to the queue
    state *temp;
    for(int i=0; i<10; i++){
        temp = nextState(s, i);
        if(validState(temp) && notFound(temp, vis)) {
            (*temp).parent = s;
            q.push(temp); // If temp is both valid and not visited, it means it's a new state that can be explored. So, it sets the parent of temp to s to keep track of the path to this state, and it pushes temp into the queue q for further exploration
        } else delete temp;
    } 
}

void printOP(int n) {
 // Print the action corresponding to the given number
  switch (n)
  {
    case 0:  cout << "C(0,1,0)" << endl; break;
    case 1:  cout << "C(0,2,0)" << endl; break;
    case 2:  cout << "C(1,0,0)" << endl; break;
    case 3:  cout << "C(2,0,0)" << endl; break;
    case 4:  cout << "C(1,1,0)" << endl; break;
    case 5:  cout << "C(0,1,1)" << endl; break;
    case 6:  cout << "C(0,2,1)" << endl; break;
    case 7:  cout << "C(1,0,1)" << endl; break;
    case 8:  cout << "C(2,0,1)" << endl; break;
    case 9:  cout << "C(1,1,1)" << endl; break;
  }
}

int main(){
    // Define initial and goal states
    // Create a queue for BFS and a vector to store visited states
    // Push the initial state to the queue
    // Perform BFS search
    // If goal state is found, print the path, else print "Path not found!
    bool fl=false;
    state START = {3,3,0,0,0,NULL,-1}; 
    // This defines the initial state of the problem, where there are 3 missionaries and 3 cannibals on the left side of the river, the boat is on the left side (pos = 0), and
    // there are no missionaries and cannibals on the right side. The parent pointer is set to NULL, and the op is set to -1 (indicating no operation).
    state GOAL = {0,0,1,3,3,NULL};

    queue<state *> q;
    vector<state *> vis;

    q.push(&START);

    state* temp; // for current state

    while(!q.empty()){ //This loop continues until the queue q is empty, meaning all possible states have been explored or the goal state has been found.
        temp = q.front();
        q.pop();
        if((*temp) == GOAL){
            fl=true;
            break;
        } else{
            addChildren(q, temp, vis);
            vis.push_back(temp);
        }
    }


//After the BFS search is completed, if (fl) { ... } else { ... }: checks if a path to the goal state was found (fl is true). If a path is found, it prints the path using the printOP function and indicates success. Otherwise, it prints "Path not found!".
    if(fl){ 
        cout << "Path found!\n";
        cout << "C(missionary, cannibal, position of boat)\n";

        stack<int> ops;
        for(state* i=temp; i!=NULL; i = (*i).parent){
            ops.push((*i).op);
        }

        while(!ops.empty()){  // This loop iterates over each action stored in the stack ops, printing them out in reverse order.
            printOP(ops.top());
            ops.pop();
        }
    } else{
        cout << "Path not found!\n";
    }

    return 0;
}