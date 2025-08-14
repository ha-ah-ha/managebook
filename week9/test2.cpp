#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n,m;
    cin>>n>>m;
    vector<ll> rank(n+1,0);
    for(ll i=0;i<m;i++){
        ll a,b;
        cin>>a>>b;
        rank[b]=a;
    }
    ll i=1;
    while(i<=n){
        if(rank[i]!=0){
            ll k=i;
            ll j=rank[i];
            while(rank[j]!=0&&rank[j]!=-1){
                k=j;
                j=rank[j];
            }
            if(rank[j]==0){cout<<j<<' ';}
            else if(rank[j]==-1){cout<<k<<' ';}
            rank[k]=0;
        }
        else{
            cout<<i<<' ';
            i++;
            rank[i]=-1;
        }
    }
    cout<<endl;
}