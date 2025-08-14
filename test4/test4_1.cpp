#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//上司的舞会
int main(){
    int n;
    cin>>n;
    if(n==1){
        cout<<"0 1"<<endl;
        return 0;
    }
    if(n==2){
        cout<<"2 2"<<endl;
    }
    vector<vector<int>> graph(n+1);
    vector<int> deg(n+1,0);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    vector<vector<int>> children(n+1);//孩子
    vector<int> parent(n+1,0);//父亲
    vector<bool> visited(n+1,false);
    queue<int> q;
    q.push(1);
    visited[1]=true;
    while(!q.empty()){//bfs构成有根树
        int u=q.front();
        q.pop();
        for(int v:graph[u]){
            if(!visited[v]){//未被访问过
                visited[v]=true;
                parent[v]=u;
                children[u].push_back(v);
                q.push(v);
            }
        }
    }

    vector<int> order;//从根节点到底部，依次记录每层的节点
    q.push(1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        order.push_back(u);
        for(int v:children[u]){
            q.push(v);
        }
    }
    reverse(order.begin(),order.end());//反转函数

    vector<int> dp_size0(n+1,0);//以节点u为根的子树中的最大独立集大小
    vector<int> dp_size1(n+1,0);
    vector<ll> dp_degsum0(n+1,0);//选中节点的度数之和
    vector<ll> dp_degsum1(n+1,0);

    for(int u:order){//从最底层叶子节点层层遍历
        dp_size0[u]=0;
        dp_degsum0[u]=0;
        dp_size1[u]=1;
        dp_degsum1[u]=deg[u];

        for(int v:children[u]){
            dp_size1[u] += dp_size0[v];//选中u一定不选中v
            dp_degsum1[u] += dp_degsum0[v];
            //未选中u所以v可以选中也可以不选中
            if (dp_size0[v] > dp_size1[v]) {
                dp_size0[u] += dp_size0[v];
                dp_degsum0[u] += dp_degsum0[v];
            } else if (dp_size0[v] < dp_size1[v]) {
                dp_size0[u] += dp_size1[v];
                dp_degsum0[u] += dp_degsum1[v];
            } else {
                dp_size0[u] += dp_size0[v];
                dp_degsum0[u] += min(dp_degsum0[v], dp_degsum1[v]);
            }
        }
    }

    int max_size;
    ll min_degsum;
    if (dp_size0[1] > dp_size1[1]) {
        max_size = dp_size0[1];
        min_degsum = dp_degsum0[1];
    } else if (dp_size0[1] < dp_size1[1]) {
        max_size = dp_size1[1];
        min_degsum = dp_degsum1[1];
    } else {
        max_size = dp_size0[1];
        min_degsum = min(dp_degsum0[1], dp_degsum1[1]);
    }

    ll total_value = min_degsum + (n - max_size);
    cout << max_size << " " << total_value << endl;
}