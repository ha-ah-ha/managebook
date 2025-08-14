#include<bits/stdc++.h>
using namespace std;
int n,m,k;
//int ans=0;
const int MOD=998244353;
// void fun(int pos,vector<bool> v){
//     if(pos==n){
//         ans=(ans+1)%998244353;
//         return;
//     }
//     for(int i=pos+1;i<=n&&i-pos<=k;i++){
//         if(v[i]!=1){
//             fun(i,v);
//         }
//     }
// }

int main(){
    
    cin>>n>>m>>k;
    vector<bool> v(n+1,0);
    for(int i=0;i<m;i++){
        int a;
        cin>>a;
        v[a]=1;
    }
    //fun(1,v);
    vector<int> dp(n+1,0);
    vector<int> pre(n+1,0);
    dp[0]=1;
    pre[0]=1;
    for(int i=1;i<=n;i++){
        if(v[i]){
            pre[i]=pre[i-1];
            continue;
        }
        int l=max(0,i-k);
        int r=i-1;
        int sum = (pre[r] - (l > 0 ? pre[l-1] : 0) + MOD) % MOD;
        dp[i] = sum;
        pre[i] = (pre[i-1] + dp[i]) % MOD;
    }
    cout << dp[n] % MOD;
}