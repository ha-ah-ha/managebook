#include<iostream>
#include<algorithm>
#include<string>
#include <windows.h>
#include<random>
#include<queue>
using namespace std;

typedef long long LL;
mt19937_64 gen(time(0));

struct node {//������ҵ�����ԣ����ڽṹ����
    int start;//��ʼʱ��
    int end;//����ʱ��
    int num;//��ҵ���
    int w;//������
    int wait = 0;//�ȴ�ʱ��
};// h[1000010];
node* e;
bool cmp(node a, node b) { return a.start < b.start; }


void loading() {//���ݴ��������
    cout << "\n���ݴ�����,���Ժ󡭡�\n";
    for (int i = 1; i <= 5; i++) {
        cout << "[";
        for (int j = 1; j <= i; j++) cout << "����";
        for (int j = 0; j < 5 - i; j++) cout << "����";
        printf("]\t%d%%", i * 20);
        Sleep(1000);
        cout << "\r";
    }
    cout << "\n\n";
    return;
}

void loading2() {//��ӡ���ݴ��������
    cout << "\n����������,���Ժ󡭡�\n";
    for (int i = 1; i <= 2; i++) {
        cout << "[";
        for (int j = 1; j <= i; j++) cout << "����������";
        for (int j = 0; j < 2 - i; j++) cout << "����������";
        printf("]\t%d%%", i * 50);
        Sleep(1000);
        cout << "\r";
    }
    cout << "\n\n";
    return;
}

bool judge(string s) {//�ж��ַ����Ƿ���ȫ�����ֹ���,���ַ����Ƿ�Ϸ�
    for (int i = 0; i < s.size(); i++)
        if (s[i] >= '0' && s[i] <= '9')
            continue;
        else
            return false;
    return true;
}

int randInt(int l, int r) {
    return gen() % (r - l + 1) + l;
}//����[l,R]��int������
LL randLL(LL l, LL r) {
    return gen() % (r - l + 1) + l;
}//����[l,R]�� long long int������

struct LeftistNode {
    int key;          // ������ pi = (end - start) - wait
    int s;            // ����루s-value��
    int start;        // ��ʼʱ��
    int end;          // ����ʱ��
    int num;          // ��ҵ���
    int wait;         // �ȴ�ʱ��
    LeftistNode* left;
    LeftistNode* right;

    LeftistNode(int k, int st, int e, int n)
        : key(k), start(st), end(e), num(n), wait(0), s(1), left(nullptr), right(nullptr) {}
};
// �ϲ����������
LeftistNode* merge(LeftistNode* a, LeftistNode* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    // ȷ�� a �Ǹ���С����
    if (a->key > b->key) swap(a, b);

    // �ݹ�ϲ�������
    a->right = merge(a->right, b);

    // ά��������ʣ��������� s ֵ >= ������
    if (a->left == nullptr || (a->left->s < a->right->s)) {
        swap(a->left, a->right);
    }

    // ���µ�ǰ�ڵ�� s ֵ
    a->s = (a->right == nullptr) ? 1 : a->right->s + 1;

    return a;
}

// �����½ڵ�
LeftistNode* insert(LeftistNode* root, LeftistNode* newNode) {
    return merge(root, newNode);
}

// ɾ����Сֵ���Ѷ���
LeftistNode* deleteMin(LeftistNode* root) {
    if (root == nullptr) return nullptr;
    LeftistNode* left = root->left;
    LeftistNode* right = root->right;
    delete root;
    return merge(left, right);
}

// �ݹ�����������͵ȴ�ʱ��
void update(LeftistNode* root, int currentTime) {
    if (root == nullptr) return;
    root->wait = currentTime - root->start;
    root->key = (root->end - root->start) - root->wait;
    update(root->left, currentTime);
    update(root->right, currentTime);
}

// �ؽ���������ȱ����ռ��ڵ㣬�����²��룩
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
    int executingUntil = -1; // ��ǰ��ҵִ�н���ʱ��

    while (currentTime <= 2000) {
        //����µ������ҵ�������
        for (int j = 0; j < k; j++) {
            if (e[j].start == currentTime) {
                int pi = e[j].end - e[j].start;
                LeftistNode* newNode = new LeftistNode(pi, e[j].start, e[j].end, e[j].num);
                root = insert(root, newNode);
            }
        }
        //��̬�����������͵ȴ�ʱ�䣬���ؽ������
        if (root != nullptr) {
            update(root, currentTime);
            root = rebuild(root); // �ؽ���ά��������
        }

        //������ҵ�������ǰ����ҵ��ִ�У�
        if (currentTime > executingUntil) {
            if (root != nullptr) {
                LeftistNode* minNode = root;
                int duration = minNode->end - minNode->start;
                executingUntil = currentTime + duration - 1;

                // ���������Ϣ
                printf("%d-���Ϊ%d����ҵ��%dʱ�������\t��%dʱ��ʼ����\t��%dʱ�뿪\t����ʱ��Ϊ%d\t�ȴ�ʱ��%d\t��������̬�仯%d -> %d\n",
                    ans++, minNode->num, minNode->start, currentTime,
                    currentTime + duration, duration, minNode->wait,
                    (minNode->end - minNode->start), minNode->key);

                // ɾ���ѵ��ȵ���ҵ
                root = deleteMin(root);
            }
        }

        currentTime++;
    }
}


void color(int x) {
    if (x == 0)  //��ɫ
        return;
    else if (x == 1)  //��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED);
    else if (x == 2)  //��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    else if (x == 3)  //��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_BLUE);
    else if (x == 4)  //��ɫ
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
    else if (x == 5)  //��ɫ
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    else if (x == 6)  //��ɫ
        SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    else if (x == 7)  //�������
        color(randInt(0, 6));
    return;
}

int main() {
    cout << "\n***************************************************\n";  //���������Ϣ
    cout << "*         -�������ȶ��е���ҵ�����㷨ʵ��-        *\n";
    cout << "*                   -�����ʵ��-                  *\n";
    cout << "***************************************************\n\n";

    cout << "\n----------������ɫ----------\n";
    cout << "0.��ɫ\n";
    cout << "1.��ɫ\n";
    cout << "2.��ɫ\n";
    cout << "3.��ɫ\n";
    cout << "4.��ɫ\n";
    cout << "5.��ɫ\n";
    cout << "6.��ɫ\n";
    cout << "7.�������\n";
    cout << "-----------------------------\n";
    cout << "\n������������������ɫ�ı��:";
    string tmp;
    while (getline(cin, tmp)) {
        if (tmp == "0" || tmp == "1" || tmp == "2" || tmp == "3" ||
            tmp == "4" || tmp == "5" || tmp == "6" || tmp == "7") {
            color(stoi(tmp));
            break;
        }
        else
            cout << "�Ƿ�����,����������:";
    }

    cout << "\n   ----------�˵�----------\n";
    cout << "   1.�ֶ�������ҵ��Ϣ\n";
    cout << "   2.�����Զ�������ҵ��Ϣ\n";
    cout << "   3.�˳�\n";
    cout << "   ------------------------\n";
    cout << "\n����������ѡ�Ĳ������:";
    string s, str;
    while (getline(cin, s)) {
        if (s == "1" || s == "2" || s == "3")
            break;
        else
            cout << "�Ƿ�����,����������:";
    }
    if (s == "1") {
        cout << "��������ҵ����:";
        while (getline(cin, str)) {
            int num = stoi(str);
            e = new node[num + 1];
            if (num == 0) {
                cout << "��ǰû����ҵ��Ҫ������\n";
                break;
            }
            cout << "�밴˳�����%d����ҵ�Ŀ�ʼʱ��ͽ���ʱ��\n", num;
            for (int i = 0; i < num; i++) {
                printf(
                    "�������%d����ҵ�Ŀ�ʼʱ��ͽ���ʱ�䣬�м��ÿո���("
                    "1<=ʱ��<=100):",
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
                        cout << "�Ƿ�����,����������:";
                }
            }
            loading();
            check(num);
            break;
        }
    }
    else if (s == "2") {
        cout << "�������Զ�������ҵ����:";
        while (getline(cin, str)) {
            loading2();
            int num = stoi(str);
            e = new node[num + 1];
            int k = 0;
            while (k != num) {
                int a = randInt(1, 100);  //���������
                int b = randInt(1, 100);
                if (a < b) {//ȥ�����ɵķǷ������
                    e[k].start = a;
                    e[k].end = b;
                    e[k].num = k + 1;
                    k++;
                }
            }
            if (k == 0) {
                cout << "��ǰû����ҵ��Ҫ������\n";
                break;
            }
            cout << "\n�Զ����ɵ���������:\n";
            for (int i = 0; i < k; i++)
                printf("��%d����ҵ�Ŀ�ʼʱ����:%d,����ʱ����:%d\n", i + 1,
                    e[i].start, e[i].end);
            loading();
            check(k);
            break;
        }
    }
    cout << "\nллʹ��\n";  //�������
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_INTENSITY | FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE);  //��������������Ϊ��ɫ
    return 0;
}
