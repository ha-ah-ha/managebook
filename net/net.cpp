#include <iostream>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int MAX_N = 10000;

// 动态规划法结构定义
struct ReverseEdge {
    int from;//前驱节点
    int weight;//边权
    ReverseEdge* next;//下一个节点指针
};

struct State {//动态规划状态
    int setcount;//放置放大器时的最小数量
    int nosetcount;//不放置时的最小数量
    int remainvalue;//不放置时的剩余可用距离
};

// 优先队列BFS结构定义
struct Edge {
    int to;//后继节点
    int weight;
    Edge* next;
};

struct NodeState {
    int count;//放大器数量
    int remaining;//剩余可用距离
};

struct PQState {//优先队列中的状态
    int u;//当前节点
    int remain;
    int count;//放大器数量
    bool operator<(const PQState& other) const {//优先队列排序
        if(count != other.count) return count > other.count;//数量少的优先
        return remain < other.remain;//剩余距离大的优先
    }
};

//动态规划
int dynamic(int n, int s, int d, ReverseEdge* adj[], int topo[]) {
    State states[MAX_N];
    for(int i=0; i<n; ++i) {//初始化
        states[i].setcount = INT_MAX;
        states[i].nosetcount = INT_MAX;
        states[i].remainvalue = 0;
    }
    //源点初始化
    states[s].setcount = 1;//假设源点必须放置
    states[s].nosetcount = 0;//特殊处理源点不放置的情况
    states[s].remainvalue = d;
    for(int i=0; i<n; ++i) {//拓扑排序处理每个节点
        int u = topo[i];
        if(u == s) continue;//源点已经处理了

        //计算放置放大器时的最优值
        int min1 = INT_MAX;
        for(ReverseEdge* e = adj[u]; e != nullptr; e = e->next) {
            int v = e->from;//前驱节点
            int current = min(states[v].setcount, states[v].nosetcount);//前驱节点v的最优选择
            min1 = min(min1, current);
        }
        if(min1 != INT_MAX) states[u].setcount = min1 + 1;

        //计算不放置放大器时的最优值
        int best_count = INT_MAX, best_remain = 0;
        for(ReverseEdge* e = adj[u]; e != nullptr; e = e->next) {
            int v = e->from;
            int w = e->weight;
            //前驱放置放大器的情况
            if(states[v].setcount != INT_MAX) {
                int rem = d - w;//从v放置后，到u的剩余距离
                if(rem >= 0 && states[v].setcount < best_count) {
                    best_count = states[v].setcount;
                    best_remain = rem;
                }
            }

            //前驱不放置放大器的情况
            if(states[v].nosetcount != INT_MAX && states[v].remainvalue >= w) {
                int rem = states[v].remainvalue - w;
                if(states[v].nosetcount < best_count) {
                    best_count = states[v].nosetcount;
                    best_remain = rem;
                }
            }
        }
        if(best_count != INT_MAX) {//更新不放置的状态
            states[u].nosetcount = best_count;
            states[u].remainvalue = best_remain;
        }

        if(states[u].setcount == INT_MAX && states[u].nosetcount == INT_MAX)
            return -1;
    }

    // 最终结果取所有节点的最大值
    int result = 0;
    for(int i=0; i<n; ++i) {
        int current = min(states[i].setcount, states[i].nosetcount);
        if(current == INT_MAX) return -1;
        result = max(result, current);
    }
    return result;
}

//优先队列BFS
int bfs(int n, int s, int d, Edge* adj[]) {
    NodeState node_states[MAX_N];
    for(int i=0; i<n; ++i) {
        node_states[i].count = INT_MAX;
        node_states[i].remaining = 0;
    }
    priority_queue<PQState> pq;
    pq.push({s, d, 0});

    while(!pq.empty()) {
        auto [u, r, c] = pq.top();
        pq.pop();

        //剪枝：已有更优状态
        if(c > node_states[u].count || (c == node_states[u].count && r <= node_states[u].remaining))
            continue;

        node_states[u].count = c;
        node_states[u].remaining = r;

        for(Edge* e = adj[u]; e != nullptr; e = e->next) {
            int v = e->to;
            int w = e->weight;

            // 不放置放大器的情况
            if(r >= w) {
                int new_r = r - w;
                if(c < node_states[v].count || (c == node_states[v].count && new_r > node_states[v].remaining)) {
                    pq.push({v, new_r, c});
                }
            }

            // 放置放大器的情况
            int new_r = d - w;
            int new_c = c + 1;
            if(new_c < node_states[v].count || (new_c == node_states[v].count && new_r > node_states[v].remaining)) {
                pq.push({v, new_r, new_c});
            }
        }
    }
    // 取所有节点的最大值
    int result = 0;
    for(int i=0; i<n; ++i) {
        if(node_states[i].count == INT_MAX) return -1;
        result = max(result, node_states[i].count);
    }
    return result;
}

//拓扑排序
void toposort(int n, Edge* adj[], int in_degree[], int topo[]) {
    queue<int> q;
    for(int i=0; i<n; ++i)
        if(in_degree[i] == 0)//入度为0的节点入队
            q.push(i);
    int idx = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        topo[idx++] = u;//记录拓扑排序
        //遍历所有出边，更新后继节点的入度
        for(Edge* e = adj[u]; e != nullptr; e = e->next) {
            int v = e->to;
            if(--in_degree[v] == 0)//入度减一
                q.push(v);
        }
    }
}

int main() {
    int n, m, d, s;
    cin >> n >> m >> d >> s;//n个节点，m条边，pmax-pmin=10，源节点s
    s--; // 转换为0-based索引

    Edge* adj[MAX_N] = {nullptr};//邻接表
    ReverseEdge* reverse_adj[MAX_N] = {nullptr};//逆邻接表
    int in_degree[MAX_N] = {0};//入度数组

    //读取输入并建图
    bool possible = true;
    for(int i=0; i<m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;//u->v,边权w
        u--; 
        v--;//转换为0-based索引
        
        if(w > d) possible = false;//存在不可达边

        //正向图
        Edge* e = new Edge{v, w, adj[u]};
        adj[u] = e;
        in_degree[v]++;//更新入度

        //反向图
        ReverseEdge* re = new ReverseEdge{u, w, reverse_adj[v]};
        reverse_adj[v] = re;
    }

    if(!possible) {
        cout << "-1\n";
        return 0;
    }

    //得到拓扑排序
    int topo[MAX_N];
    toposort(n, adj, in_degree, topo);

    //运行动态规划
    auto start = high_resolution_clock::now();//计时
    int dp_result = dynamic(n, s, d, reverse_adj, topo);
    auto stop = high_resolution_clock::now();
    auto dp_duration = duration_cast<microseconds>(stop - start);

    //运行BFS
    start = high_resolution_clock::now();
    int bfs_result = bfs(n, s, d, adj);
    stop = high_resolution_clock::now();
    auto bfs_duration = duration_cast<microseconds>(stop - start);

    //输出结果
    cout << "动态规划结果: " << dp_result << "\n";
    cout << "BFS结果: " << bfs_result << "\n";
    cout << "动态规划的时间: " << dp_duration.count() << "μs\n";
    cout << "BFS的时间: " << bfs_duration.count() << "μs\n";

    //释放内存
    for(int i=0; i<n; ++i) {
        while(adj[i]) {
            Edge* temp = adj[i];
            adj[i] = adj[i]->next;
            delete temp;
        }
        while(reverse_adj[i]) {
            ReverseEdge* temp = reverse_adj[i];
            reverse_adj[i] = reverse_adj[i]->next;
            delete temp;
        }
    }

    return 0;
}