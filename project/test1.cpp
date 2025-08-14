#include<iostream>
#include<algorithm>
#include<string>
#include <windows.h>
#include<random>
#include<queue>
using namespace std;

typedef long long LL;
mt19937_64 gen(time(0));

struct node {//定义作业的属性，放在结构体里
    int start;//开始时间
    int end;//结束时间
    int num;//作业编号
    int w;//优先数
    int wait = 0;//等待时间
}h[1000010];
node* e;
bool cmp(node a, node b) { return a.start < b.start;}

int randInt(int l, int r) {
    return gen() % (r - l + 1) + l;
}//生成[l,R]的int型数字
LL randLL(LL l, LL r) {
    return gen() % (r - l + 1) + l;
}//生成[l,R]的 long long int型数字

struct LeftistNode {
    int key;          // 优先数 pi = (end - start) - wait
    int s;            // 零距离（s-value）
    int start;        // 开始时间
    int end;          // 结束时间
    int num;          // 作业编号
    int wait;         // 等待时间
    LeftistNode* left;
    LeftistNode* right;

    LeftistNode(int k, int st, int e, int n) 
        : key(k), start(st), end(e), num(n), wait(0), s(1), left(nullptr), right(nullptr) {}
};
// 合并两棵左高树
LeftistNode* merge(LeftistNode* a, LeftistNode* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    // 确保 a 是根较小的树
    if (a->key > b->key) swap(a, b);

    // 递归合并右子树
    a->right = merge(a->right, b);

    // 维护左高性质：左子树的 s 值 >= 右子树
    if (a->left == nullptr || (a->left->s < a->right->s)) {
        swap(a->left, a->right);
    }

    // 更新当前节点的 s 值
    a->s = (a->right == nullptr) ? 1 : a->right->s + 1;

    return a;
}

// 插入新节点
LeftistNode* insert(LeftistNode* root, LeftistNode* newNode) {
    return merge(root, newNode);
}

// 删除最小值（堆顶）
LeftistNode* deleteMin(LeftistNode* root) {
    if (root == nullptr) return nullptr;
    LeftistNode* left = root->left;
    LeftistNode* right = root->right;
    delete root;
    return merge(left, right);
}

// 递归更新优先数和等待时间
void updatePriorities(LeftistNode* root, int currentTime) {
    if (root == nullptr) return;
    root->wait = currentTime - root->start;
    root->key = (root->end - root->start) - root->wait;
    updatePriorities(root->left, currentTime);
    updatePriorities(root->right, currentTime);
}

// 重建左高树（先遍历收集节点，再重新插入）
LeftistNode* rebuildTree(LeftistNode* root) {
    if (root == nullptr) return nullptr;
    vector<LeftistNode*> nodes;
    queue<LeftistNode*> q;
    q.push(root);
    while (!q.empty()) {
        LeftistNode* node = q.front();
        q.pop();
        nodes.push_back(node);
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    LeftistNode* newRoot = nullptr;
    for (auto node : nodes) {
        node->left = node->right = nullptr;
        newRoot = insert(newRoot, node);
    }
    return newRoot;
}

void check(int k) {
    sort(e, e + k, [](node a, node b) { return a.start < b.start; });
    int ans = 1;
    int currentTime = 1;
    LeftistNode* root = nullptr;
    int executingUntil = -1; // 当前作业执行结束时间

    while (currentTime <= 2000) {
        // 1. 添加新到达的作业到左高树
        for (int j = 0; j < k; j++) {
            if (e[j].start == currentTime) {
                int pi = e[j].end - e[j].start;
                LeftistNode* newNode = new LeftistNode(pi, e[j].start, e[j].end, e[j].num);
                root = insert(root, newNode);
            }
        }

        // 2. 动态更新优先数和等待时间，并重建左高树
        if (root != nullptr) {
            updatePriorities(root, currentTime);
            root = rebuildTree(root); // 重建以维护堆性质
        }

        // 3. 调度作业（如果当前无作业在执行）
        if (currentTime > executingUntil) {
            if (root != nullptr) {
                LeftistNode* minNode = root;
                int duration = minNode->end - minNode->start;
                executingUntil = currentTime + duration - 1;

                // 输出调度信息
                printf("%d-编号为%d的作业于%d时进入队列\t于%d时开始调度\t于%d时离开\t调度时长为%d\t等待时间%d\t优先数动态变化%d -> %d\n",
                       ans++, minNode->num, minNode->start, currentTime,
                       currentTime + duration, duration, minNode->wait,
                       (minNode->end - minNode->start), minNode->key);

                // 删除已调度的作业
                root = deleteMin(root);
            }
        }

        currentTime++;
    }
}