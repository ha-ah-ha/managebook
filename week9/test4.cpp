#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    //邻接表得到原图和逆图
    vector<vector<int>> adj(n+1),radj(n+1);
    for(int i=0;i<m;++i){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);//原图
        radj[b].push_back(a);//逆图
    }
    // Kosaraju算法第一步：获取逆后序
    vector<bool> visited(n+1,false);
    stack<int> order;//存储逆后序的栈
    for(int i=1;i<=n;++i){
        if(!visited[i]){//使用显示栈模拟DFS递归，避免栈溢出
            stack<pair<int,bool>> s;//节点和是否被处理
            s.push({i,false});
            while(!s.empty()){
                auto [u,p]=s.top();
                s.pop();
                if(p){
                    order.push(u);//已经处理的节点按完成时间压栈
                    continue;
                }
                if(visited[u])//已经被访问了
                    continue;
                visited[u]=true;
                s.push({u,true});//重新压入并标记为已处理
                for(int v:adj[u]){//将为访问的邻接节点逆序压栈，保证DFS顺序
                    if(!visited[v]){
                        s.push({v,false});
                    }
                }
            }
        }
    }
    //处理逆图
    vector<int> id(n+1,0);//记录每个节点所属的编号
    int cur=0;//当前编号
    vector<bool> visited2(n+1,false);
    while(!order.empty()){
        int u=order.top();
        order.pop();
        if(!visited2[u]){
            cur++;
            stack<int> s;
            s.push(u);
            visited2[u]=true;
            id[u]=cur;
            while(!s.empty()){
                int v=s.top();
                s.pop();//在逆图上遍历
                for(int w:radj[v]){
                    if(!visited2[w]){
                        visited2[w]=true;
                        id[w]=cur;
                        s.push(w);
                    }
                }
            }
        }
    }
    //构建缩点DAG并计算入度
    vector<unordered_set<int>> scc_adj(cur + 1);//邻接表，去重
    vector<int> in_degree(cur+ 1, 0);//入度统计

    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            int a = id[u];
            int b = id[v];
            if (a != b && scc_adj[a].insert(b).second) {//如果a和b属于不同SCC且边未添加过
                in_degree[b]++;
            }
        }
    }
    //统计入度为0的节点数量
    int ans=0;
    for(int i=1;i<=cur;i++){
        if(in_degree[i]==0){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}