#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll llm = LLONG_MAX;
vector<ll> dij(int start, const vector<vector<pair<int, int>>> &graph, int n) {
    vector<ll> dist(n + 1, llm);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;//已找到更短路径，跳过

        for (auto [v, c] : graph[u]) {
            if (dist[v] > d + c) {
                dist[v] = d + c;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        ll n,m;//车站数量，单向路径数
        cin>>n>>m;
        //map<pair<int,int>,ll> path;
        vector<vector<pair<int,int>>> pathto(n+1);
        vector<vector<pair<int,int>>> pathback(n+1);
        for(ll i=0;i<m;i++){
            ll s,e,c;
            cin>>s>>e>>c;
            pathto[s].emplace_back(e,c);//正向边
            pathback[e].emplace_back(s,c);//反向边
        }
        vector<ll> disto=dij(1,pathto,n);
        vector<ll> disback=dij(1,pathback,n);
        ll sumvalue=0;
        for(int i=2;i<=n;++i){
            sumvalue+=disto[i]+disback[i];
        }
        cout<<sumvalue<<"\n";
    }
}