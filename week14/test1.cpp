#include<bits/stdc++.h>
using namespace std;

int depthnum[100002],depths[100002]={0};
vector<vector<int>> tree;
bool vis[100002]={0};
int depth=0,num=0;
void dfs(int root){
    for(auto &i:tree[root]){
        if(vis[i]==0){
            vis[i]=1;
            dfs(i);
            if(depths[i]+depths[root]+1>depth){
                depth=depths[i]+depths[root]+1;
                num=depthnum[i]*depthnum[root];
            }
            else if(depths[i]+depths[root]+1==depth){
                num+=depthnum[i]*depthnum[root];
            }
            if(depths[i]+1>depths[root]){
                depths[root]=depths[i]+1;
                depthnum[root]=depthnum[i];
            }
            else if(depths[i]+1==depths[root]){
                depthnum[root]+=depthnum[i];
            }
        }
    }
}

int main(){
    int n;
    cin>>n;
    tree.resize(n+1);
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    for(int i=0;i<=n;i++){
        depthnum[i]=1;
    }
    vis[1]=1;
    dfs(1);
    cout<<depth<<' '<<num;
}