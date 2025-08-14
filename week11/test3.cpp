#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n;
    cin>>n;
    vector<vector<int>> v(n+1);
    for(int i=1;i<=3;i++){
        for(int j=1;j<=n;j++){
            ll a=0;
            cin>>a;
            v[j].push_back(a);
        }
    }
    vector<vector<ll>> dp(n+1);
    for(int i=0;i<3;i++){dp[1].push_back(0);}
    for(ll i=2;i<=n;i++){
        dp[i].push_back(min({dp[i-1][0]+abs(v[i][0]-v[i-1][0]),dp[i-1][1]+abs(v[i][0]-v[i-1][1]),dp[i-1][2]+abs(v[i][0]-v[i-1][2])}));
        dp[i].push_back(min({dp[i-1][0]+abs(v[i][1]-v[i-1][0]),dp[i-1][1]+abs(v[i][1]-v[i-1][1]),dp[i-1][2]+abs(v[i][1]-v[i-1][2])}));
        dp[i].push_back(min({dp[i-1][0]+abs(v[i][2]-v[i-1][0]),dp[i-1][1]+abs(v[i][2]-v[i-1][1]),dp[i-1][2]+abs(v[i][2]-v[i-1][2])}));
    }
    cout<<min({dp[n][0],dp[n][1],dp[n][2]});
}