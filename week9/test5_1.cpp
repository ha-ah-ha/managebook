#include<bits/stdc++.h>
using namespace std;
const int N = 1e4;
const double eps = 1e-4;

struct Edge {
    int to, v, p;
};

int n, m;
vector<Edge> e[N];
double dis[N];
int cnt[N];
bool inqueue[N];

bool hascycle(double mid){
    queue<int> q;
    for(int i=1;i<=n;i++){
        dis[i]=0;
        cnt[i]=0;
        inqueue[i]=true;
        q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        inqueue[u]=false;
        for(auto& it:e[u]){
            double w=mid*it.p-it.v;
            int v=it.to;
            if (dis[v] > dis[u] + w + eps) { // 使用eps避免浮点误差
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) {
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

int main(){
    cin>>n>>m;
    for(int i=0;i<m;++i){
        int u,v,V,P;
        cin>>u>>v>>V>>P;
        e[u].push_back({v,V,P});
    }
    double left=0,right=1e4;
    double ans=0;
    for(int i=0;i<100;++i){
        double mid=(left+right)/2;
        if (hascycle(mid)) {
            ans = mid;
            left = mid;
        } else {
            right = mid;
        }
    }
    printf("%.1lf\n", ans);
    return 0;
}