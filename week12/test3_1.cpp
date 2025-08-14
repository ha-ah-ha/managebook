#include<bits/stdc++.h>
using namespace std;
//二进制优化
using ll = long long;
const int N = 1e6 + 5;
ll w[N], c[N], f[N]; int cnt;//重量 价值 dp 当前处理的物品总数
void f1(ll a, ll b)
{
	cnt++;
	w[cnt] = a; c[cnt] = b;
}
int n,V;
int main() {
	cin >> n >> V;
	while (n--)
	{
		ll w, v, c;
		cin >> w >> v >> c;
		for (int i = 1; i <= c; i *= 2)f1(w * i, v * i),c -= i;
		if (c > 0)f1(w * c, v * c);
	}
	for (int i = 1; i <= V; ++i)f[i] = 0;
	for (int i = 1; i <= cnt; ++i)
		for (int j = V; j >= 1; --j)
			if (j -w[i] >= 0)f[j] = max(f[j], f[j - w[i] ]+ c[i]);
	cout << f[V];
}