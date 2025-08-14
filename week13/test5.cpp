#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


int main(){
    ll n,k;
    cin>>n>>k;
    vector<ll> a(n);//数据
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    vector<vector<bool>> is(n,vector<bool>(n,false));//标记元素对是否满足|a[i]-a[j]|>k
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(abs(a[j]-a[i])>k){
                is[i][j]=true;//允许a[i]与a[j]相邻
            }
        }
    }
    vector<vector<ll>> dp(1<<n,vector<ll>(n,0));//表示已选集合为mask，最后元素是j的情况数目
    for(int i=0;i<n;i++){
        dp[1<<i][i]=1;//初始化单元素的排列数目均为1
    }
    for(int i=1;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if(!(i&(1<<j))) continue;//当j不在当前集合中，跳过
            for(int m=0;m<n;m++){
                if(i&(1<<m)) continue;//m已经被选中，跳过
                if(is[j][m]){//允许j后接m
                    int newi=i|(1<<m);
                    dp[newi][m]+=dp[i][j];//更新状态
                }
            }
        }
    }
    long long ans = 0;//统计结果
    int full_mask = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        ans += dp[full_mask][i];//全选状态下所有可能结尾元素的情况数目之和
    }
    cout << ans << endl;
}