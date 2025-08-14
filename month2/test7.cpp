#include<bits/stdc++.h>
using namespace std;

bool containsSeven(int num) {
    if (num == 0) return false;
    while (num != 0) {
        int digit = num % 10;
        if (digit == 7)
            return true;
        num /= 10;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> ans(n, 0);
    for (int k = 1; k <= m; ++k) {
        int person = (k - 1) % n + 1;
        if (k % 7 == 0 || containsSeven(k)) {
            ans[person - 1]++;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    return 0;
}