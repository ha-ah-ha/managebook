#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int F;
    cin >> F;
    while (F--) {
        int n, m, w;
        cin >> n >> m >> w;
        map<pair<int, int>, int> road_edges;
        for (int i = 0; i < m; ++i) {
            int s, e, t;
            cin >> s >> e >> t;
            pair<int, int> key1 = {s, e};
            pair<int, int> key2 = {e, s};
            if (!road_edges.count(key1) || t < road_edges[key1]) {
                road_edges[key1] = t;
            }
            if (!road_edges.count(key2) || t < road_edges[key2]) {
                road_edges[key2] = t;
            }
        }
        map<pair<int, int>, int> wormholes;
        for (int i = 0; i < w; ++i) {
            int s, e, t;
            cin >> s >> e >> t;
            pair<int, int> key = {s, e};
            if (!wormholes.count(key) || t > wormholes[key]) {
                wormholes[key] = t;
            }
        }
        vector<Edge> edges;
        for (auto &entry : road_edges) {
            edges.push_back({entry.first.first, entry.first.second, entry.second});
        }
        for (auto &entry : wormholes) {
            edges.push_back({entry.first.first, entry.first.second, -entry.second});
        }
        vector<int> dist(n + 1, 0);
        bool has_negative_cycle = false;
        for (int i = 0; i < n; ++i) {
            bool updated = false;
            for (auto &edge : edges) {
                if (dist[edge.u] + edge.w < dist[edge.v]) {
                    dist[edge.v] = dist[edge.u] + edge.w;
                    updated = true;
                }
            }
            if (!updated) break;
        }
        for (auto &edge : edges) {
            if (dist[edge.u] + edge.w < dist[edge.v]) {
                has_negative_cycle = true;
                break;
            }
        }
        cout << (has_negative_cycle ? "YES" : "NO") << endl;
    }
    return 0;
}