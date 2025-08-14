#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct goods
{
    ll w;
    ll v;
    ll k;
    goods(ll w1,ll v1,ll k1):w(w1),v(v1),k(k1){}
};
int main(){
    ll n,v;
    cin>>n>>v;
    vector<goods> e;
    ll cnt;
    for(ll i=0;i<n;i++){
        ll w,v,k;
        cin>>w>>v>>k;
        ll a=1;
        while(a<=k){
            goods g(a*w,v*a,1);
            e.push_back(g);
            k-=a;
            a*=2;
        }
        if(k){
            goods g(k*w,k*v,1);
            e.push_back(g);
        }
        // goods g(w,v,k);
        // e.push_back(g);
    }
    vector<ll> dp(v+1,0);
    for(ll i=0;i<e.size();i++){
        //if(e[i].k*e[i].w>=v){
            for(ll j=v;j>=e[i].w;j--){
                dp[j]=max(dp[j],dp[j-e[i].w]+e[i].v);
            }
        //}
        // else{
        //     for(ll j=v;j>=e[i].w;j--){
        //         for(ll k=e[i].k;k>=0;k--){
        //             if(j>=k*e[i].w){
        //                 dp[j]=max(dp[j-k*e[i].w]+k*e[i].v,dp[j]);
        //             }
        //         }
        //     }
        // }
    }
    cout<<dp[v];
}