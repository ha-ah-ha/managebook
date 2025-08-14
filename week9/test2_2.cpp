#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n+1);
    vector<int> in(n+1,0);
    for(int i=0;i<m;++i){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        in[b]++;
    }
    priority_queue<int,vector<int>,greater<int> > pq;
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            pq.push(i);
        }
    }
    vector<int> res;
    while(!pq.empty()){
        int u=pq.top();
        pq.pop();
        res.push_back(u);
        for(auto it:adj[u]){
            if(--in[it]==0){
                pq.push(it);
            }
        }

    }
    for(auto it:res){
        cout<<it<<" ";
    }
}