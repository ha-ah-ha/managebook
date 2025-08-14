#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,v;
    cin>>n>>v;
    vector<pair<int,int>> e;
    for(int i=0;i<n;i++){
        int w,v;
        cin>>w>>v;
        e.push_back({w,v});
    }
    vector<int> dp(v+1,0);
    dp[0]=0;
    for(int i=0;i<n;i++){
        for(int j=e[i].first;j<=v;j++){
            if(j>=e[i].first){
                dp[j]=max(dp[j],dp[j-e[i].first]+e[i].second);
            }
        }
    }
    cout<<dp[v];
    return 0;
}