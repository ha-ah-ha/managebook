#include<bits/stdc++.h>
using namespace std;

struct Edge {//定义一个结构体Edge用于存储边的信息
    int u, v, w;
};

int main(){
    int F;
    cin>>F;//测试用例数
    while (F--)//对于每个测试用例
    {
        int n,m,w;
        cin>>n>>m>>w;//输入图的节点数n，边数m，虫洞边数w
        //使用map存储普通边（路径）和虫洞边（时间）
        map<pair<int,int>,int> path;//普通路径
        map<pair<int,int>,int> timepath;//虫洞边
        //对于普通边
            for (int i = 0; i < m; ++i) {
                int s, e, t;
                cin >> s >> e >> t;
                if (path.count({s, e}) == 0 || t < path[{s, e}]) {//当未存储该边或者当前时间更小时
                    path[{s, e}] = t;
                    path[{e, s}] = t;
                }//取时间值最小的双向边存入
            }
        for(int i=0;i<w;i++){//虫洞边
            int s,e,t;
            cin>>s>>e>>t;
            if (timepath.count({s, e}) == 0 || t > timepath[{s, e}]) {//当未存储该边或者当前时间更大时
                timepath[{s, e}] = t;
            }//取时间值最大的虫洞边存入
        }
        vector<Edge> edges;//用一个edges向量来存储所有边，包括普通路径和虫洞边
        for (auto &entry : path) {
            edges.push_back({entry.first.first, entry.first.second, entry.second});//将普通路径存入edges向量
        }
        for (auto &entry : timepath) {
            edges.push_back({entry.first.first, entry.first.second, -entry.second});//将虫洞边存入 edges 向量，虫洞的时间取负值（目的是将虫洞视为负权重边）
        }
        // int* visited=new int[n+1];
        // for(int i=1;i<n+1;i++){
        //     visited[i]=0;
        // }
        vector<int> dist(n + 1, 0);//路径距离初始化为0
        bool hascycle = false;//判断是否有负权环
        for (int i = 0; i < n; ++i) { //进行Bellman-Ford算法的n-1次松弛操作
            bool updated = false;
            for (auto &edge : edges) {
                //如果通过当前边可以更新到目标节点的最短路径
                if (dist[edge.u] + edge.w < dist[edge.v]) {
                    dist[edge.v] = dist[edge.u] + edge.w;//更新最短路径
                    updated = true;//标记有更新
                }
            }
            if (!updated) break;//如果没有更新，说明已经找到最短路径，提前结束循环
        }
        //再次松弛检测是否有负权环
        for (auto &edge : edges) {
            if (dist[edge.u] + edge.w < dist[edge.v]) {
                hascycle = true;//如果可以更新路径，说明图中存在负权环
                break;
            }
        }
        cout << (hascycle ? "YES" : "NO") << endl;//输出
    }
    return 0;
}