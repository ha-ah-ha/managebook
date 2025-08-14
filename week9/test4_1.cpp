#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    //邻接表得到原图和逆图
    vector<vector<int>> adj(n + 1), r_adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);//原图
        r_adj[b].push_back(a);//逆图
    }

    // Kosaraju算法第一步：获取逆后序
    vector<bool> visited(n + 1, false);
    stack<int> order;//存储逆后序的栈

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {//使用显示栈模拟DFS递归，避免栈溢出
            stack<pair<int, bool>> s;//节点和是否被处理
            s.push({i, false});
            while (!s.empty()) {
                auto [u, processed] = s.top();
                s.pop();
                if (processed) {
                    order.push(u);//已经处理的节点按完成时间压栈
                    continue;
                }
                if (visited[u]) continue;//已经被访问了
                visited[u] = true;
                s.push({u, true});//重新压入并标记为已处理
                for (int v : adj[u]) {//将为访问的邻接节点逆序压栈，保证DFS顺序
                    if (!visited[v]) {
                        s.push({v, false});
                    }
                }
            }
        }
    }

    // Kosaraju算法第二步：处理逆图
    vector<int> scc_id(n + 1, 0);
    int current_scc = 0;
    vector<bool> visited2(n + 1, false);

    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (!visited2[u]) {
            current_scc++;
            stack<int> s;
            s.push(u);
            visited2[u] = true;
            scc_id[u] = current_scc;
            while (!s.empty()) {
                int v = s.top();
                s.pop();
                for (int w : r_adj[v]) {
                    if (!visited2[w]) {
                        visited2[w] = true;
                        scc_id[w] = current_scc;
                        s.push(w);
                    }
                }
            }
        }
    }

    // 构建缩点后的DAG并计算入度
    vector<unordered_set<int>> scc_adj(current_scc + 1);
    vector<int> in_degree(current_scc + 1, 0);

    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            int a = scc_id[u];
            int b = scc_id[v];
            if (a != b && scc_adj[a].insert(b).second) {
                in_degree[b]++;
            }
        }
    }

    // 统计入度为0的分量数目
    int ans = 0;
    for (int i = 1; i <= current_scc; ++i) {
        if (in_degree[i] == 0) {
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}