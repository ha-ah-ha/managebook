#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<tuple<int,int,int>> e;
    for (int i = 1; i <= n; i++) {
        e.push_back({i-1, i, 1});
        e.push_back({i, i-1, 0});
    }
    for(int i =1;i<=m;i++){
        int k,a,b,c;
        cin>>k>>a>>b>>c;
        int u=a-1;
        int v=b;
        if(k==1){//s[v]-s[u]<=c
            e.push_back({u,v,c});
        }
        if(k==2){//s[v]-s[u]>=c
            e.push_back({v,u,-c});
        }
        if(k==3){//s[v]-s[u]<=c-1
            e.push_back({u,v,c-1});
        }
        if(k==4){//c+1
            e.push_back({v,u,-c-1});
        }
        if(k==5){
            e.push_back({u,v,c});
            e.push_back({v,u,-c});
        }
    }
    vector<long long> d(n+1,LLONG_MIN);
    vector<long long> vis(n+1);
    d[0]=0;
    vis[0]=1;
    bool hascycle=false;
    for(int i=0;i<=n;++i){
        bool updated=false;
        for(auto [u,v,c]:e){
            if(d[u]!=LLONG_MIN&&d[v]<d[u]+c){
                d[v]=d[u]+c;
                updated=true;
            }
        }
        if(updated&&i==n){
            hascycle=true;
        }
    }
    if(hascycle||d[n]==LLONG_MIN){
        cout<<"impossible"<<endl;
    }
    else{
        cout<<d[n]<<endl;
    }
    return 0;
}