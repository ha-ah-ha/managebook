#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll, ll> fib_pair(ll n, ll p) {
    if (n == 0)
        return {0 % p, 1 % p};
    auto p_vals = fib_pair(n >> 1, p);
    ll a = p_vals.first;
    ll b = p_vals.second;
    ll c = (a * ((2 * b + a) % p)) % p;
    ll d = (a * a % p + b * b % p) % p;
    if (n % 2 == 0)
        return {c, d};
    else
        return {(c + d) % p, c};
}

ll fast_fib(ll n, ll p) {
    if (n == 0) return 0;
    return fib_pair(n, p).first;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n, p;
        cin >> n >> p;
        cout << fast_fib(n, p) % p << "\n";
    }
    return 0;
}