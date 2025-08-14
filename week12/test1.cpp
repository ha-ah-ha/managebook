#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,v;
    cin>>n>>v;
    vector<pair<int,int>> e;
    e.push_back({0,0});
    for(int i=0;i<n;i++){
        int w,c;
        cin>>w>>c;
        e.push_back({w,c});
    }
    vector<vector<int>> f(n+1,vector<int>(v+1,0));
    for(int i=1;i<=n;i++){
        for(int j=v;j>=0;j--){
            if(j>=e[i].first){
                f[i][j]=max(f[i-1][j],f[i-1][j-e[i].first]+e[i].second);
            }
            else{
                f[i][j]=f[i-1][j];
            }
        }
    }
    int ans=f[n][v];
    cout<<ans<<endl;
}