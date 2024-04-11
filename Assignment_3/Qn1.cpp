#include <bits/stdc++.h>

using namespace std;

#define ll long long

void nextPermutation(vector<ll>& nums) {
    int n = nums.size(), k, l;// eg :1 2 4 5 3 ans should be 1 2 5 3 4
    for (k = n - 2; k >= 0; k--) {
        if (nums[k] < nums[k + 1]) {
            break;
        }
    }
    if (k < 0) { //which means no element is found such that it's less than its adjacent right element. eg.[5, 4, 3, 2, 1]
    	reverse(nums.begin(), nums.end()); 
    } else {
    	for (l = n - 1; l > k; l--) {
            if (nums[l] > nums[k]) {
                break;
            }
        } 
    	swap(nums[k], nums[l]);
    	reverse(nums.begin() + k + 1, nums.end());
    }
}
// 3 4 2 1 
// 4 3 2 1
// 4 1 2 3

int main(){
    cout << "Enter the size of array!\n";
    ll n;
    cin >> n;
    vector<ll> a(n);
    cout << "Enter elements of array:\n";
    for(ll i=0; i<n; i++){
        cin >> a[i];
    }
    nextPermutation(a);
    for(int i=0; i<n; i++){
        cout << a[i] << " ";
    }
    cout << "\n";
}
