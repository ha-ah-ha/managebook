#include<bits/stdc++.h>
using namespace std;

struct node {
    int father;
    map<string, int> child;
    int type; // 1是文件，2是目录
    long long ld, lr; // 目录配额，后代配额
    long long size; // 普通文件的大小
    long long ld_r, lr_r; // 实际孩子文件的大小总和，实际后代文件大小总和
};
node nodes[4000000];
int num = 0;
vector<pair<int, string>> reback;

void Reback() {
    for (auto &p : reback) {
        int a = p.first;
        string b = p.second;
        nodes[a].child.erase(b);
    }
}

void build() {
    string path;
    int size1;
    cin >> path >> size1;
    int last = -1;
    for (last = path.length() - 1; last >= 0; last--) {
        if (path[last] == '/') break;
    }
    if (last == -1) { // 无效路径？
        cout << "N\n";
        return;
    }
    int t = 1;
    int id = 0;
    reback.clear();
    int oldnum = num;
    while (t < last) {
        string cur;
        while (t < last && path[t] != '/') {
            cur += path[t];
            t++;
        }
        t++;
        if (nodes[id].child.find(cur) == nodes[id].child.end()) {
            num++;
            nodes[id].child[cur] = num;
            reback.emplace_back(id, cur);
            nodes[num].father = id;
            nodes[num].type = 2;
            nodes[num].ld = LLONG_MAX;
            nodes[num].lr = LLONG_MAX;
            nodes[num].ld_r = 0;
            nodes[num].lr_r = 0;
            id = num;
        } else {
            int childid = nodes[id].child[cur];
            if (nodes[childid].type == 1) {
                num = oldnum;
                Reback();
                cout << "N\n";
                return;
            }
            id = childid;
        }
    }
    string cur;
    for (int i = last + 1; i < path.length(); i++) {
        cur += path[i];
    }
    if (cur.empty()) {
        num = oldnum;
        Reback();
        cout << "N\n";
        return;
    }
    if (nodes[id].child.find(cur) != nodes[id].child.end()) {
        int childid = nodes[id].child[cur];
        if (nodes[childid].type == 2) {
            num = oldnum;
            Reback();
            cout << "N\n";
            return;
        }
    }
    long long changesize = size1;
    if (nodes[id].child.find(cur) != nodes[id].child.end()) {
        int childid = nodes[id].child[cur];
        changesize -= nodes[childid].size;
    }
    if (nodes[id].ld_r + changesize > nodes[id].ld) {
        num = oldnum;
        Reback();
        cout << "N\n";
        return;
    }
    int now = id;
    while (now != -1) {
        if (nodes[now].lr_r + changesize > nodes[now].lr) {
            num = oldnum;
            Reback();
            cout << "N\n";
            return;
        }
        now = nodes[now].father;
    }
    if (nodes[id].child.find(cur) == nodes[id].child.end()) {
        num++;
        nodes[num].father = id;
        nodes[num].type = 1;
        nodes[num].size = size1;
        nodes[id].child[cur] = num;
    } else {
        nodes[nodes[id].child[cur]].size = size1;
    }
    nodes[id].ld_r += changesize;
    now = id;
    while (now != -1) {
        nodes[now].lr_r += changesize;
        now = nodes[now].father;
    }
    cout << "Y\n";
}

void erase() {
    string path;
    cin >> path;
    int last = -1;
    for (int i = path.length() - 1; i >= 0; i--) {
        if (path[i] == '/') {
            last = i;
            break;
        }
    }
    if (last == -1) {
        cout << "Y\n";
        return;
    }
    int id = 0;
    int t = 1;
    while (t < last) {
        string cur;
        while (t < last && path[t] != '/') {
            cur += path[t];
            t++;
        }
        t++;
        if (nodes[id].child.find(cur) == nodes[id].child.end()) {
            cout << "Y\n";
            return;
        }
        id = nodes[id].child[cur];
        if (nodes[id].type == 1) {
            cout << "Y\n";
            return;
        }
    }
    string cur;
    for (int i = last + 1; i < path.length(); i++) {
        cur += path[i];
    }
    if (nodes[id].child.find(cur) == nodes[id].child.end()) {
        cout << "Y\n";
        return;
    }
    int delid = nodes[id].child[cur];
    long long changesize = 0;
    if (nodes[delid].type == 1) {
        changesize = nodes[delid].size;
        nodes[id].ld_r -= changesize;
    } else {
        changesize = nodes[delid].lr_r;
    }
    nodes[id].child.erase(cur);
    int now = id;
    while (now != -1) {
        nodes[now].lr_r -= changesize;
        now = nodes[now].father;
    }
    cout << "Y\n";
}

void reset() {
    string path;
    long long ld1, lr1;
    cin >> path >> ld1 >> lr1;
    if (ld1 == 0) ld1 = LLONG_MAX;
    if (lr1 == 0) lr1 = LLONG_MAX;
    int last = -1;
    for (int i = path.length() - 1; i >= 0; i--) {
        if (path[i] == '/') {
            last = i;
            break;
        }
    }
    if (last == -1) {
        cout << "N\n";
        return;
    }
    int id = 0;
    int t = 1;
    while (t < last) {
        string cur;
        while (t < last && path[t] != '/') {
            cur += path[t];
            t++;
        }
        t++;
        if (nodes[id].child.find(cur) == nodes[id].child.end()) {
            cout << "N\n";
            return;
        }
        id = nodes[id].child[cur];
        if (nodes[id].type == 1) {
            cout << "N\n";
            return;
        }
    }
    string cur;
    for (int i = last + 1; i < path.length(); i++) {
        cur += path[i];
    }
    int qid;
    if (path == "/") {
        qid = 0;
    } else {
        if (nodes[id].child.find(cur) == nodes[id].child.end()) {
            cout << "N\n";
            return;
        }
        qid = nodes[id].child[cur];
    }
    if (nodes[qid].type == 1) {
        cout << "N\n";
        return;
    }
    if (ld1 < nodes[qid].ld_r || lr1 < nodes[qid].lr_r) {
        cout << "N\n";
        return;
    }
    nodes[qid].ld = ld1;
    nodes[qid].lr = lr1;
    cout << "Y\n";
}

int main() {
    int n;
    cin >> n;
    nodes[0].type = 2;
    nodes[0].father = -1;
    nodes[0].ld = LLONG_MAX;
    nodes[0].lr = LLONG_MAX;
    nodes[0].ld_r = 0;
    nodes[0].lr_r = 0;
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        if (op == 'C') build();
        else if (op == 'R') erase();
        else if (op == 'Q') reset();
    }
    return 0;
}