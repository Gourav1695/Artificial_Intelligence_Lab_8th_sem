#include<bits/stdc++.h>

using namespace std;

#define ll long long

void shift(int n, char src, char intermediate, char dest){
    if(!n){
        return;
    }
    shift(n - 1, src, dest, intermediate);
    cout << "Disc " << n << " moves from pole " << src << " to pole " << dest << endl;
    shift(n - 1, intermediate, src, dest);
}

void solve(){
    int n, k = -1;
    cout << "Enter number of discs: ";
    cin >> n;
    shift(n, 'A', 'B', 'C');
    cout << endl;
}
int main()
{
    int t;
    cout << "Enter number of test cases: ";
    cin >> t;
    while(t--){
        solve();
    }
}