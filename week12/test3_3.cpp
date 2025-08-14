#include<bits/stdc++.h>
using namespace std;
const int NUM = 1005;
const int NN = 105;
int N, V,cnt,k;
using ll = long long;
ll dp[NUM], w, c;
vector<pair<int,ll> > vl[NN];
int main() {
    cin >> N >> V;
    for (int i = 0; i < NN; i++) vl[i].emplace_back(0, 0);
    for (int i = 1; i <= N; i++) {
        cin >> w >> c >> k;//体积 价值 组别
        vl[k].emplace_back(w,c);//放入对应组别
        cnt = max(k, cnt);
    }
    for (int k = 1; k <= cnt; ++k)//倒序遍历  防止重复
        for (int i = V; i >= 0; --i)
            for (int j = 1; j < vl[k].size(); ++j)
                if (i >= vl[k][j].first)
                    dp[i] = max(dp[i], dp[i - vl[k][j].first] + vl[k][j].second);
    cout << dp[V];
}