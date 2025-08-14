#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

struct Edge {
	int v, w, next;//目标节点v，边权w，下一条边索引
}edge[20100];

int head[20100], vis[20100], dis[20100], cnt[20100];//邻接表头，访问标记，距离，入队次数
int tot;//边总数

void add(int x, int y, int z) {//添加边x->y，权z
	edge[tot].v = y;
	edge[tot].w = z;
	edge[tot].next = head[x];
	head[x] = tot++;
}

int main()
{
	int n, m, k, a, b, c;
	cin >> n >> m;
	tot = 0;
	memset(head, -1, sizeof(head));//初始化邻接表
	memset(dis, INF, sizeof(dis));//距离初始化为无穷
	memset(vis, 0, sizeof(vis));//访问标记清零
	memset(cnt, 0, sizeof(cnt));//入队次数清零
	for (int i = 0; i < m; i++) {//处理m条约束
		cin >> k >> a >> b >> c;
		if (k == 1) {//edge[b]-edge[a-1]<=c
			add(a - 1, b, c);
		}
		else if (k == 2) {//edge[b]-edge[a-1]>=c
			add(b, a - 1, -c);
		}
		else if (k == 3) {//edge[b]-edge[a-1]<=c-1
			add(a - 1, b, c - 1);
		}
		else if (k == 4) {//edge[b]-edge[a-1]>=c-1
			add(b, a - 1, -c + 1);
		}
		else if (k == 5) {//edge[b]-edge[a-1]=c
			add(a - 1, b, c);
			add(b, a - 1, -c);
		}
	}
	//添加额外的约束
	for (int i = 0; i < n; i++) {
		add(i, i + 1, 1);//edge[i+1]-edge[i]<=1
		add(i + 1, i, 0);//edge[i+1]-edge[i]>=0
	}
	//SPFA算法
	dis[0] = 0;//起点距离为0
	vis[0] = 1;
	queue<int> q;
	q.push(0);
	int flag = 0;//标记是否有负环
	int now;
	while (!q.empty()) {
		now = q.front();
		q.pop();
		vis[now] = 0;//出队清除标记
		for (int i = head[now]; i != -1; i = edge[i].next) {
			if (dis[edge[i].v] > dis[now] + edge[i].w) {//松弛操作
				dis[edge[i].v] = dis[now] + edge[i].w;
				cnt[edge[i].v] = cnt[now] + 1;
				if (cnt[edge[i].v] >= n) {//入队次数超过n，存在负环
					flag = 1;
					break;
				}
				if (vis[edge[i].v] == 0) {//若未在队列中，入队
					vis[edge[i].v] = 1;
					q.push(edge[i].v);
				}
			}
		}
		if (flag == 1) {
			break;
		}
	}
	if (flag == 1) {
		cout << "impossible" << endl;//存在负环
	}
	else {
		cout << dis[n] << endl;//输出结果
	}
	return 0;

}