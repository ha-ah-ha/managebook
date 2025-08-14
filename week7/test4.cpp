#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
vector<ll>* e;
ll vis[100001]={0};
ll dis[100001]={0};
ll d1[100001]={0};
ll d2[100001]={0};
void bfs(ll p,ll dis1[]){
    queue<ll> q1;
    q1.push(p);
    vis[p]=1;
    while(!q1.empty()){
        ll root=q1.front();
        q1.pop();
        for(int i=0;i<e[root].size();i++){
            if(vis[e[root][i]]==0){
                q1.push(e[root][i]);
                vis[e[root][i]]=1;
                dis1[e[root][i]]=dis1[root]+1;
            }
        }
    }
}
int main(){
    ll n;
    cin>>n;
    e=new vector<ll>[n+1];
    for(ll i=1;i<n;i++){
        ll a,b;
        cin>>a>>b;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    ll p1,p2;
    bfs(1,dis);
    //找到p1
    int maxlength=0;
    for(int i=0;i<=n;i++){
        vis[i]=0;
        if(maxlength<dis[i]){
            p1=i;
            maxlength=dis[i];
        }
    }
    bfs(p1,d1);
    maxlength=0;
    for(int i=0;i<=n;i++){
        vis[i]=0;
        if(maxlength<d1[i]){
            p2=i;
            maxlength=d1[i];
        }
    }
    bfs(p2,d2);

    for(ll i=1;i<=n;i++){
        cout<<max(d1[i],d2[i])<<' ';
    }
}