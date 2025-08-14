#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n,v;
    cin>>n>>v;
    vector<pair<ll,ll>> e;
    e.push_back({0,0});
    for(ll i=0;i<n;i++){
        ll w,c;
        cin>>w>>c;
        e.push_back({w,c});
    }
    vector<vector<ll>> f(n+1);
    for(ll i=0;i<=n;i++){
        vector<ll> a(v+1,0);
        f[i]=a;
    }
    for(ll i=1;i<=n;i++){
        for(ll j=v;j>=0;j--){
            if(j>=e[i].first){
                f[i][j]=max(f[i-1][j],f[i-1][j-e[i].first]+e[i].second);
            }
            else{
                f[i][j]=f[i-1][j];
            }
        }
    }
    ll ans=f[n][v];
    cout<<ans<<endl;
}