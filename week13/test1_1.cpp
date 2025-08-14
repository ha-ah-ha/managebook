#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> v(2 * n + 1);  // 扩展为环形数组
    vector<ll> dp(2 * n + 1, 0);
    
    // 输入并扩展数组
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        v[i + n] = v[i];  // 复制到后半部分
    }
    
    // 计算前缀和
    for (int i = 1; i <= 2 * n; i++) {
        dp[i] = dp[i - 1] + v[i];
    }
    
    // 初始化DP表
    vector<vector<ll>> min1(2 * n + 1, vector<ll>(2 * n + 1, LLONG_MAX));
    vector<vector<ll>> max1(2 * n + 1, vector<ll>(2 * n + 1, LLONG_MIN));
    for (int i = 1; i <= 2 * n; i++) {
        min1[i][i] = 0;  // 单个石子无需合并
        max1[i][i] = 0;
    }
    
    // 动态规划计算所有区间
    for (int len = 2; len <= n; len++) {  // 合并后的总长度为n
        for (int i = 1; i + len - 1 <= 2 * n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                ll sum = dp[j] - dp[i - 1];
                // 更新最小值
                if (min1[i][k] != LLONG_MAX && min1[k+1][j] != LLONG_MAX) {
                    min1[i][j] = min(min1[i][j], min1[i][k] + min1[k+1][j] + sum);
                }
                // 更新最大值
                if (max1[i][k] != LLONG_MIN && max1[k+1][j] != LLONG_MIN) {
                    max1[i][j] = max(max1[i][j], max1[i][k] + max1[k+1][j] + sum);
                }
            }
        }
    }
    // 遍历所有起点获取全局极值
    ll min_ans = LLONG_MAX, max_ans = LLONG_MIN;
    for (int i = 1; i <= n; i++) {
        int j = i + n - 1;  // 合并n个石子的区间终点
        min_ans = min(min_ans, min1[i][j]);
        max_ans = max(max_ans, max1[i][j]);
    }
    cout << min_ans << "\n" << max_ans << "\n";
}