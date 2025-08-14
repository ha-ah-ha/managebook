#include<bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<long long>>;

// 矩阵乘法
Matrix matrixMultiply(const Matrix& a, const Matrix& b, long long mod) {
    Matrix res(2, vector<long long>(2));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return res;
}
// 矩阵快速幂
Matrix matrixPower(Matrix a, long long power, long long mod) {
    Matrix res = {{1, 0}, {0, 1}}; // 单位矩阵
    while (power > 0) {
        if (power & 1) {
            res = matrixMultiply(res, a, mod);
        }
        a = matrixMultiply(a, a, mod);
        power >>= 1;
    }
    return res;
}

// 计算斐波那契数列第n项模p
long long fibonacci(long long n, long long p) {
    if (n == 1 || n == 2) return 1 % p;
    
    Matrix mat = {{1, 1}, {1, 0}};
    Matrix result = matrixPower(mat, n - 2, p);
    return (result[0][0] + result[0][1]) % p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        long long n, p;
        cin >> n >> p;
        cout << fibonacci(n, p) << '\n';
    }
    
    return 0;
}