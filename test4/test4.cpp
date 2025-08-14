#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    if (n == 1) {
        cout << "0 1" << endl;
        return 0;
    }

    vector<vector<int>> graph(n + 1);
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    if (n == 2) {
        cout << "2 2" << endl;
        return 0;
    }

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                children[u].push_back(v);
                q.push(v);
            }
        }
    }

    vector<int> order;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : children[u]) {
            q.push(v);
        }
    }
    reverse(order.begin(), order.end());

    vector<int> dp_size0(n + 1, 0);
    vector<int> dp_size1(n + 1, 0);
    vector<LL> dp_degsum0(n + 1, 0);
    vector<LL> dp_degsum1(n + 1, 0);

    for (int u : order) {
        dp_size0[u] = 0;
        dp_degsum0[u] = 0;
        dp_size1[u] = 1;
        dp_degsum1[u] = deg[u];

        for (int v : children[u]) {
            dp_size1[u] += dp_size0[v];
            dp_degsum1[u] += dp_degsum0[v];

            if (dp_size0[v] > dp_size1[v]) {
                dp_size0[u] += dp_size0[v];
                dp_degsum0[u] += dp_degsum0[v];
            } else if (dp_size0[v] < dp_size1[v]) {
                dp_size0[u] += dp_size1[v];
                dp_degsum0[u] += dp_degsum1[v];
            } else {
                dp_size0[u] += dp_size0[v];
                dp_degsum0[u] += min(dp_degsum0[v], dp_degsum1[v]);
            }
        }
    }

    int max_size;
    LL min_degsum;
    if (dp_size0[1] > dp_size1[1]) {
        max_size = dp_size0[1];
        min_degsum = dp_degsum0[1];
    } else if (dp_size0[1] < dp_size1[1]) {
        max_size = dp_size1[1];
        min_degsum = dp_degsum1[1];
    } else {
        max_size = dp_size0[1];
        min_degsum = min(dp_degsum0[1], dp_degsum1[1]);
    }

    LL total_value = min_degsum + (n - max_size);
    cout << max_size << " " << total_value << endl;

    return 0;
}