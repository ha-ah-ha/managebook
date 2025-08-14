#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 1e5; // 最大的n值
const int maxprime = 100; // 最大的质数数目

// 获取c的所有质因数及其指数
void getprime(int c, vector<int>& primes, vector<int>& exps) {
    if (c == 1) return;
    for (int i = 2; i * i <= c; i++) {
        if (c % i == 0) {
            primes.push_back(i);
            int cnt = 0;
            while (c % i == 0) {
                c = c / i;
                cnt++;
            }
            exps.push_back(cnt);
        }
    }
    if (c > 1) {
        primes.push_back(c);
        exps.push_back(1);
    }
}

int mod_pow(long long a, long long b) {
    long long result = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;

    // 哈希表存储每个质因数对应的差分数组
    unordered_map<int, vector<long long>> a;

    // 处理每个操作
    for (int i = 0; i < m; i++) {
        int l, r, c;
        long long b;
        cin >> l >> r >> c >> b;

        if (c == 1) continue; // 乘以1不影响结果

        vector<int> primes, exps;
        getprime(c, primes, exps);
        
        // 更新每个质因数的差分数组
        for (int j = 0; j < primes.size(); j++) {
            int z = primes[j];
            long long sumexp = (long long)exps[j] * b;

            // 如果没有初始化这个质因数的差分数组，则初始化
            if (a.find(z) == a.end()) {
                a[z] = vector<long long>(n + 2, 0);
            }

            // 差分数组的更新
            a[z][l] += sumexp;
            if (r + 1 <= n) {
                a[z][r + 1] -= sumexp;
            }
        }
    }

    // 计算每个质因数的最小指数并求最终的结果
    long long gcd = 1;
    for (auto& p : a) {
        int prime = p.first;
        vector<long long>& diff = p.second;

        long long current = 0;
        long long min_exp = LLONG_MAX;

        // 计算前缀和，找到最小的指数
        for (int i = 1; i <= n; i++) {
            current += diff[i];
            min_exp = min(min_exp, current);
        }

        // 如果最小指数大于0，则累乘该质因数的最小指数
        if (min_exp > 0) {
            gcd = (gcd * mod_pow(prime, min_exp)) % mod;
        }
    }

    // 输出最终结果
    cout << gcd << endl;

    return 0;
}
