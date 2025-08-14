#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const double eps = 1e-4;

struct Edge {
    int to, V, P;
};

int n, m;
vector<Edge> edges[N];
double dis[N];
int cnt[N];
bool inqueue[N];

bool hasNegativeCycle(double mid) {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {//初始化
        dis[i] = 0;
        cnt[i] = 0;
        inqueue[i] = true;
        q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;
        for (auto &e : edges[u]) {
            double w = mid * e.P - e.V;//关键转化
            int v = e.to;
            if (dis[v] > dis[u] + w + eps) { //可松弛 使用eps避免浮点误差
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) {//检测到负环
                    return true;
                }
                if (!inqueue[v]) {
                    q.push(v);
                    inqueue[v] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, V, P;
        cin >> u >> v >> V >> P;
        edges[u].push_back({v, V, P});
    }

    double left = 0, right = 1e4;//二分查找
    double ans = 0;
    for (int iter = 0; iter < 100; ++iter) {
        double mid = (left + right) / 2;
        if (hasNegativeCycle(mid)) {
            ans = mid;
            left = mid;
        } else {
            right = mid;
        }
    }

    printf("%.1lf\n", ans);
    return 0;
}