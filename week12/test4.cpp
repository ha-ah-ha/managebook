#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct goods
{
    int w;
    int v;
    goods(int w1,int v1):w(w1),v(v1){}
};

int main(){
    int n,v;
    cin>>n>>v;
    int cnt=0;
    vector<vector<goods>> e(105);

    for(int i=0;i<n;i++){
        int w,v1,k;
        cin>>w>>v1>>k;
        goods g(w,v1);
        e[k].push_back(g);
        cnt=max(k,cnt);
    }
    vector<int> dp(v+1,0);
    for(int i=0;i<105;i++){
        for(int j=v;j>=0;j--){
            for(int k=0;k<e[i].size();k++){
                if(e[i][k].w<=j){
                    dp[j]=max(dp[j],dp[j-e[i][k].w]+e[i][k].v);
                }
            }
        }
    }
    cout<<dp[v];
}