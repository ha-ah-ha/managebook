#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    string s;
    cin>>s;
    int n=s.size();
    if(n==0){
        cout<<0<<endl;
        return 0;
    }
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        dp[i][i]=1;
    }
    for(int len=2;len<=n;len++){
        for(int i=0;i+len<=n;i++){
            int j=i+len-1;
            dp[i][j]=INT_MAX;
            if((s[i]=='('&&s[j]==')')||(s[i]=='['&&s[j]==']')){
                dp[i][j]=(i+1<=j-1) ? dp[i+1][j-1]:0;
            }
            for(int k=i;k<j;k++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
    }
    cout<<dp[0][n-1]<<endl;
    return 0;
}