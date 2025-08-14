#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<ll> sum_suffix(n + 2, 0);
    for (int i = n - 1; i >= 0; --i) {
        sum_suffix[i] = a[i] + sum_suffix[i + 1];
    }
    vector<ll> cross_sum(n + 2, 0);
    for (int i = n - 1; i >= 0; --i) {
        cross_sum[i] = a[i] * sum_suffix[i + 1] + cross_sum[i + 1];
    }
    vector<ll> sq_sum(n + 2, 0);
    for (int i = n - 1; i >= 0; --i) {
        sq_sum[i] = (a[i] * a[i] + a[i]) / 2 + sq_sum[i + 1];
    }
    vector<ll> pre(n + 1, 0);
    ll h = 0;
    for (int i = 0; i < n; ++i) {
        pre[i + 1] = pre[i] + h * a[i] + (a[i] * (a[i] + 1)) / 2;
        h += a[i];
    }
    ll min_total = pre[n];
    for (int k = 0; k < n; ++k) {
        int m = k + 1;
        ll current = pre[m] + (cross_sum[m] + sq_sum[m]);
        if (current < min_total) {
            min_total = current;
        }
    }
    cout << min_total << endl;
    return 0;
}