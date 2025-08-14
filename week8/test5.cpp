#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int X;
    cin>>X;
    while(X--){
        int n,m,t;
        cin>>n>>m>>t;
        vector<vector<tuple<ll,ll,ll>>> path(n+1);
        ll maxc=0;
        for(int i=0;i<m;i++){
            ll a,b,c,d;
            cin>>a>>b>>c>>d;
            path[a].emplace_back(b,c,d);
            path[b].emplace_back(a,c,d);
            maxc=max(maxc,c);
        }
        ll left=0,right=maxc;
        ll ans=0;
        while(left<=right){
            ll mid=(left+right)/2;
            vector<ll> dist(n+1,LONG_MAX);
            priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq;
            dist[1]=0;
            pq.emplace(0,1);
            while(!pq.empty()){
                auto [d,u]=pq.top();
                pq.pop();
                if(d>dist[u]) continue;
                if(u==n) break;
                for(const auto& [a,b,c]:path[u]){
                    if(b>=mid){
                        if(dist[a]>d+c){
                            dist[a]=d+c;
                            pq.emplace(dist[a],a);
                        }
                    }
                }
            }
            if(dist[n]<=t){
                ans=mid;
                left=mid+1;
            }
            else{
                right=mid-1;
            }
        }
        cout<<ans<<"\n";
    }
}