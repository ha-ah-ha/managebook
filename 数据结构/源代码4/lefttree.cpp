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
};// h[1000010];
node* e;
bool cmp(node a, node b) { return a.start < b.start; }


void loading() {//数据处理进度条
    cout << "\n数据处理中,请稍后……\n";
    for (int i = 1; i <= 5; i++) {
        cout << "[";
        for (int j = 1; j <= i; j++) cout << "■■";
        for (int j = 0; j < 5 - i; j++) cout << "□□";
        printf("]\t%d%%", i * 20);
        Sleep(1000);
        cout << "\r";
    }
    cout << "\n\n";
    return;
}

void loading2() {//打印数据处理进度条
    cout << "\n数据生成中,请稍后……\n";
    for (int i = 1; i <= 2; i++) {
        cout << "[";
        for (int j = 1; j <= i; j++) cout << "■■■■■";
        for (int j = 0; j < 2 - i; j++) cout << "□□□□□";
        printf("]\t%d%%", i * 50);
        Sleep(1000);
        cout << "\r";
    }
    cout << "\n\n";
    return;
}

bool judge(string s) {//判断字符串是否完全由数字构成,即字符串是否合法
    for (int i = 0; i < s.size(); i++)
        if (s[i] >= '0' && s[i] <= '9')
            continue;
        else
            return false;
    return true;
}

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
void update(LeftistNode* root, int currentTime) {
    if (root == nullptr) return;
    root->wait = currentTime - root->start;
    root->key = (root->end - root->start) - root->wait;
    update(root->left, currentTime);
    update(root->right, currentTime);
}

// 重建左高树（先遍历收集节点，再重新插入）
LeftistNode* rebuild(LeftistNode* root) {
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
        //添加新到达的作业到左高树
        for (int j = 0; j < k; j++) {
            if (e[j].start == currentTime) {
                int pi = e[j].end - e[j].start;
                LeftistNode* newNode = new LeftistNode(pi, e[j].start, e[j].end, e[j].num);
                root = insert(root, newNode);
            }
        }
        //动态更新优先数和等待时间，并重建左高树
        if (root != nullptr) {
            update(root, currentTime);
            root = rebuild(root); // 重建以维护堆性质
        }

        //调度作业（如果当前无作业在执行）
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


void color(int x) {
    if (x == 0)  //白色
        return;
    else if (x == 1)  //红色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED);
    else if (x == 2)  //绿色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    else if (x == 3)  //蓝色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    else if (x == 4)  //粉色
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
    else if (x == 5)  //青色
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    else if (x == 6)  //黄色
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    else if (x == 7)  //随机生成
        color(randInt(0, 6));
    return;
}

int main() {
    cout << "\n***************************************************\n";  //输出文字信息
    cout << "*         -基于优先队列的作业调度算法实现-        *\n";
    cout << "*                   -左高树实现-                  *\n";
    cout << "***************************************************\n\n";

    cout << "\n----------字体颜色----------\n";
    cout << "0.白色\n";
    cout << "1.红色\n";
    cout << "2.绿色\n";
    cout << "3.蓝色\n";
    cout << "4.粉色\n";
    cout << "5.青色\n";
    cout << "6.黄色\n";
    cout << "7.随机生成\n";
    cout << "-----------------------------\n";
    cout << "\n请输入您想用字体颜色的编号:";
    string tmp;
    while (getline(cin, tmp)) {
        if (tmp == "0" || tmp == "1" || tmp == "2" || tmp == "3" ||
            tmp == "4" || tmp == "5" || tmp == "6" || tmp == "7") {
            color(stoi(tmp));
            break;
        }
        else
            cout << "非法输入,请重新输入:";
    }

    cout << "\n   ----------菜单----------\n";
    cout << "   1.手动输入作业信息\n";
    cout << "   2.电脑自动生成作业信息\n";
    cout << "   3.退出\n";
    cout << "   ------------------------\n";
    cout << "\n请输入您所选的操作编号:";
    string s, str;
    while (getline(cin, s)) {
        if (s == "1" || s == "2" || s == "3")
            break;
        else
            cout << "非法输入,请重新输入:";
    }
    if (s == "1") {
        cout << "请输入作业个数:";
        while (getline(cin, str)) {
            int num = stoi(str);
            e = new node[num + 1];
            if (num == 0) {
                cout << "当前没有作业需要被调度\n";
                break;
            }
            cout << "请按顺序给出%d个作业的开始时间和结束时间\n", num;
            for (int i = 0; i < num; i++) {
                printf(
                    "请输入第%d个作业的开始时间和结束时间，中间用空格间隔("
                    "1<=时间<=100):",
                    i + 1);
                string str1, str2;
                while (cin >> str1) {
                    cin >> str2;
                    if (judge(str1) && judge(str2) && stoi(str1) >= 1 &&
                        stoi(str1) <= 100 && stoi(str2) >= 1 &&
                        stoi(str2) <= 100 && stoi(str2) > stoi(str1)) {
                        e[i].start = stoi(str1);
                        e[i].end = stoi(str2);
                        e[i].num = i + 1;
                        break;
                    }
                    else
                        cout << "非法输入,请重新输入:";
                }
            }
            loading();
            check(num);
            break;
        }
    }
    else if (s == "2") {
        cout << "请输入自动生成作业个数:";
        while (getline(cin, str)) {
            loading2();
            int num = stoi(str);
            e = new node[num + 1];
            int k = 0;
            while (k != num) {
                int a = randInt(1, 100);  //生成随机数
                int b = randInt(1, 100);
                if (a < b) {//去掉生成的非法随机数
                    e[k].start = a;
                    e[k].end = b;
                    e[k].num = k + 1;
                    k++;
                }
            }
            if (k == 0) {
                cout << "当前没有作业需要被调度\n";
                break;
            }
            cout << "\n自动生成的数据如下:\n";
            for (int i = 0; i < k; i++)
                printf("第%d个作业的开始时间是:%d,结束时间是:%d\n", i + 1,
                    e[i].start, e[i].end);
            loading();
            check(k);
            break;
        }
    }
    cout << "\n谢谢使用\n";  //程序结束
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_INTENSITY | FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE);  //将字体重新设置为白色
    return 0;
}
