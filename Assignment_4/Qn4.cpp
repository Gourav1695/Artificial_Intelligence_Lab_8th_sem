#include <bits/stdc++.h>

using namespace std;

struct state {
    int tl, tr, cl, cr, gl, gr, pos;
    state *parent;
    int op;
    bool operator==(const state & rhs) const{
        return ((tl == rhs.tl) && (tr == rhs.tr) && (cl == rhs.cl) && (cr == rhs.cr) && (pos  == rhs.pos) && (gl == rhs.gl) && (gr == rhs.gr));
    }
};

state * nextState(state *Z, const int j) {
  state * S = new state();
  (*S) = (*Z);
  (*S).op  = j;
  switch (j)
  {
    case 0: {  (*S).pos  -= 1; 
               (*S).tl += 1;
               (*S).tr -= 1;}
            break;
    case 1: {  (*S).pos  -= 1;
               (*S).cl += 1;
               (*S).cr -= 1;}
            break;  
    case 2: {  (*S).pos  -= 1;
               (*S).gl += 1;
               (*S).gr -= 1;}
            break;  
    case 3: {  (*S).pos  -= 1;}
            break;
    case 4: {  (*S).pos  += 1; 
               (*S).tr += 1;
               (*S).tl -= 1;}
            break;
    case 5: {  (*S).pos  += 1;
               (*S).cr += 1;
               (*S).cl -= 1;}
            break;  
    case 6: {  (*S).pos  += 1;
               (*S).gr += 1;
               (*S).gl -= 1;}
            break;  
    case 7: {  (*S).pos  += 1;}
            break;                      
  }
  return S;
}

bool validState(state *S){
  if(( (*S).cl < 0) || ( (*S).cl > 1)) return false;
  if(( (*S).cr < 0) || ( (*S).cr > 1)) return false;
  if(( (*S).gl < 0) || ( (*S).gl > 1)) return false;
  if(( (*S).gr < 0) || ( (*S).gr > 1)) return false;
  if(( (*S).tl < 0) || ( (*S).tl > 1)) return false;
  if(( (*S).tr < 0) || ( (*S).tr > 1)) return false;
  if(( (*S).pos != 0) && ( (*S).pos != 1))  return false;  
  if(( (*S).tl == 1 && (*S).gl == 1 && (*S).pos == 1)) return false;
  if(( (*S).cl == 1 && (*S).gl == 1 && (*S).pos == 1)) return false;
  if(( (*S).tr == 1 && (*S).gr == 1 && (*S).pos == 0)) return false;
  if(( (*S).cr == 1 && (*S).gr == 1 && (*S).pos == 0)) return false;

  return true;
}

bool notFound(state *s, vector<state *> &vis){
    for(int i=0; i<vis.size(); i++){
        if((*s) == (*(vis[i]))) return false;
    }
    return true;
}

void addChildren(queue<state *> &q, state *s, vector<state *> &vis){
    // cout << "S\n";
    // cout << (*s).tl << " " << (*s).gl << " " << (*s).cl << " " << (*s).pos << "\n";
    state *temp;
    for(int i=0; i<8; i++){
        temp = nextState(s, i);
        // cout << (*temp).tl << " " << (*temp).gl << " " << (*temp).cl << " " << (*temp).pos << "\n";
        if(validState(temp) && notFound(temp, vis)) {
            (*temp).parent = s;
            q.push(temp);
        } else delete temp;
    } 
}

void printOP(int n) {
  switch (n)
  {
    // tiger, goat, cabbage, boat
    case 0:  cout << "C(1,0,0,0)" << endl; break;
    case 1:  cout << "C(0,0,1,0)" << endl; break;
    case 2:  cout << "C(0,1,0,0)" << endl; break;
    case 3:  cout << "C(0,0,0,0)" << endl; break;
    case 4:  cout << "C(1,0,0,1)" << endl; break;
    case 5:  cout << "C(0,0,1,1)" << endl; break;
    case 6:  cout << "C(0,1,0,1)" << endl; break;
    case 7:  cout << "C(0,0,0,1)" << endl; break;
  }
}

int main(){

    bool fl=false;
    state START = {1,0,1,0,1,0,0,NULL,-1};
    state GOAL = {0,1,0,1,0,1,1,NULL};

    queue<state *> q;
    vector<state *> vis;

    q.push(&START);

    state* temp;

    while(!q.empty()){
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

    if(fl){
        cout << "Path found!\n";
        cout << "C(tiger, goat, cabbage, position of boat)\n";

        stack<int> ops;
        for(state* i=temp; i!=NULL; i = (*i).parent){
            ops.push((*i).op);
        }

        while(!ops.empty()){
            printOP(ops.top());
            ops.pop();
        }
    } else{
        cout << "Path not found!\n";
    }

    return 0;
}