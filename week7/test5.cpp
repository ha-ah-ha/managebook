#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n,m,p;
    cin>>n>>m>>p;
    vector<tuple<ll,ll,ll>> e;
    for(int i=0;i<m;i++){
        ll a,b,c;
        cin>>a>>b>>c;
        tuple<ll,ll,ll> t={a,b,c};
        e.push_back(t);
    }
    for (int i = 1; i <= n; ++i) {
        e.emplace_back(0, i, p);
    }
    sort(e.begin(),e.end(),[](const auto& a,const auto& b){
        return get<2>(a)<get<2>(b);
    });
    vector<int> fa(n+1);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> find=[&](int x){
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    };
    ll ans=0;
    for(auto& [u,v,w]:e){
        u=find(u),v=find(v);
        if(u!=v){
            fa[u]=v;
            ans+=w;
        }
    }
    cout<<ans;
}