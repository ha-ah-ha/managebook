#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int n;
    cin>>n;
    vector<ll> v(2*n+1);
    vector<ll> dp(2*n+1,0);
    for(int i=1;i<=n;i++){
        cin>>v[i];
        v[i + n] = v[i];
    }
    for(int i=1;i<=2*n;i++){
        dp[i]=dp[i-1]+v[i];
    }
    vector<vector<ll>> min1(2*n+1,vector<ll>(2*n+1,LLONG_MAX));
    vector<vector<ll>> max1(2*n+1,vector<ll>(2*n+1,LLONG_MIN));
    for(int i=1;i<=2*n;i++){
        min1[i][i]=0;
        max1[i][i]=0;
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=2*n;i++){
            int j=i+len-1;
            for(int k = i; k < j; k++){
                ll sum = dp[j] - dp[i - 1];
                if (min1[i][k] != LLONG_MAX && min1[k+1][j] != LLONG_MAX) {
                    min1[i][j] = min(min1[i][j], min1[i][k] + min1[k+1][j] + sum);
                }
                if (max1[i][k] != LLONG_MIN && max1[k+1][j] != LLONG_MIN) {
                    max1[i][j] = max(max1[i][j], max1[i][k] + max1[k+1][j] + sum);
                }
            }
        }
    }
    ll min_ans = LLONG_MAX, max_ans = LLONG_MIN;
    for (int i = 1; i <= n; i++) {
        int j = i + n - 1;//合并n个石子的区间终点
        min_ans = min(min_ans, min1[i][j]);
        max_ans = max(max_ans, max1[i][j]);
    }
    cout << min_ans << "\n" << max_ans << "\n";
    // cout<<min1[1][n]<<"\n";
    // cout<<max1[1][n]<<"\n";
}