#include<bits/stdc++.h>
using namespace std;

long long l, r, k;

int main() {
    cin >> l >> r >> k;
     long long ans = 1;
     bool found = false;

//处理k为1的特殊情况
    if (k == 1) {
        if (ans >= l && ans <= r) {
             cout << ans << endl;
             found = true;
        }
     } else {
// 确保ans从 >= l 的最小幂开始
        while (ans < l && ans <= r / k) { // 检查ans > 0以防止溢出
            ans *= k;
        }
        while (ans >= l && ans <= r) {
            cout << ans << " ";
             found = true;
// 防止溢出
            if (ans > r / k) break;
             ans *= k;
         }
     }
     
    if (!found) {
         cout << -1 << endl;
    } else {
         cout << endl; // 确保输出后换行
     }
     
     return 0;
}