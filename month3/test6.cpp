#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    unordered_map<int, int> v;
    int i = n;
    for (int j = n - 1; j >= 0; --j) {
        if (v.find(a[j]) != v.end()) {
            i = min(i, v[a[j]]);
        }
        v[a[j]] = j;
    }
    
    cout << i << endl;
    
    return 0;
}