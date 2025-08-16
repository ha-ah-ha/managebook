#include<iostream>
#include<string>
#include <windows.h>
#include<random>
using namespace std;

typedef long long LL;
mt19937_64 gen(time(0));

struct node {//������ҵ�����ԣ����ڽṹ����
    int start;//��ʼʱ��
    int end;//����ʱ��
    int num;//��ҵ���
    int w;//������
    int wait = 0;//�ȴ�ʱ��
}h[1000010];
node* e;
bool cmp(node a, node b) { return a.start < b.start;}

int randInt(int l, int r) {
    return gen() % (r - l + 1) + l;
}//����[l,R]��int������
LL randLL(LL l, LL r) {
    return gen() % (r - l + 1) + l;
}//����[l,R]�� long long int������

void loading() {//���ݴ��������
    cout<<"\n���ݴ�����,���Ժ󡭡�\n";
    for (int i = 1; i <= 5; i++) {
        cout<<"[";
        for (int j = 1; j <= i; j++) cout<<"����";
        for (int j = 0; j < 5 - i; j++) cout<<"����";
        printf("]\t%d%%", i * 20);
        Sleep(1000);
        cout<<"\r";
    }
    cout<<"\n\n";
    return;
}

void loading2() {//��ӡ���ݴ��������
    cout<<"\n����������,���Ժ󡭡�\n";
    for (int i = 1; i <= 2; i++) {
        cout<<"[";
        for (int j = 1; j <= i; j++) cout<<"����������";
        for (int j = 0; j < 2 - i; j++) cout<<"����������";
        printf("]\t%d%%", i * 50);
        Sleep(1000);
        cout<<"\r";
    }
    cout<<"\n\n";
    return;
}

int heapsize = 0;//��С������ҵ����

void insert(int x, int k) {//������С��
    h[++heapsize].w = x;
    h[heapsize].num = k;
    int t = heapsize;
    while (t > 1 && h[t / 2].w > h[t].w) {
        swap(h[t],h[t / 2]);
        t/= 2;
    }
    h[t].w = x;
    return;
}
void renew(int u) {//������С��
    int t = u;
    if (2 * u <= heapsize && h[2 * u].w < h[t].w) t = 2 * u;
    if (2 * u + 1 <= heapsize && h[2 * u + 1].w < h[t].w) t = 2 * u + 1;
    if (t != u) {
        swap(h[t], h[u]);
        renew(t);
    }
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

void check(int k)//���Ⱥ��ĺ���
{
    int ans = 1;//������ż�����
    sort(e, e + k, cmp);//����ʼʱ������������ҵ
    int flag = 0;//CPUռ�ñ�־��0Ϊ���У�
    int time=0;//��ǰ���Ƚ���ʱ��
    int a = 0;
    for (int i = 1; i <= 2000; i++) {//ģ��ʱ�����ţ�1~2000ʱ�䵥λ��
        if (i == time) flag = 0;//��鵱ǰʱ���Ƿ����ǰһ������
        for (int j = 0; j < k; j++)
        {
            if (e[j].start == i)
            {
                insert(e[j].end, j);//����ǰʱ�䵽�����ҵ�����
                a++;
            }
            /*else {
                break;
            }*/
        }
        if (heapsize > 0) {//����ǰ�ɵ�����ҵ
            if (flag == 0) {//����ʱ���е���
                int tot = h[1].num;
                int weight = h[1].w;
                swap(h[1], h[heapsize]);
                heapsize--;
                renew(1);
                time = i + e[tot].end - e[tot].start;
                printf("%d-���Ϊ%d����ҵ��%dʱ�������\t��%dʱ��ʼ����\t��%dʱ�뿪\t����ʱ��Ϊ%d\t�ȴ�ʱ��%d\t��������̬�仯%d -> %d\n",
                    ans++, e[tot].num, e[tot].start, i,
                    i + e[tot].end - e[tot].start, e[tot].end - e[tot].start,
                    e[tot].wait,e[tot].end-e[tot].start, e[tot].end - i);
                flag = 1;//�������ҵ���ڵ���
                
            }
            for (int idx = 1; idx <= heapsize; idx++) {
                e[h[idx].num].wait=i- e[h[idx].num].start;//���µȴ�ʱ��
                h[idx].w = (e[h[idx].num].end - e[h[idx].num].start) - e[h[idx].num].wait;//�������İ���
            }
        }
    }
    return;
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
    cout<<"\n***************************************************\n";  //���������Ϣ
    cout<<"*         -�������ȶ��е���ҵ�����㷨ʵ��-        *\n";
    cout<<"*                   -��С��ʵ��-                  *\n";
    cout<<"***************************************************\n\n";
    cout<<"\n----------������ɫ----------\n";
    cout<<"0.��ɫ\n";
    cout<<"1.��ɫ\n";
    cout<<"2.��ɫ\n";
    cout<<"3.��ɫ\n";
    cout<<"4.��ɫ\n";
    cout<<"5.��ɫ\n";
    cout<<"6.��ɫ\n";
    cout<<"7.�������\n";
    cout<<"-----------------------------\n";
    cout<<"\n������������������ɫ�ı��:";
    string tmp;
    while (getline(cin, tmp)) {
        if (tmp == "0" || tmp == "1" || tmp == "2" || tmp == "3" ||
            tmp == "4" || tmp == "5" || tmp == "6" || tmp == "7") {
            color(stoi(tmp));
            break;
        }
        else
            cout<<"�Ƿ�����,����������:";
    }

    cout<<"\n   ----------�˵�----------\n";
    cout<<"   1.�ֶ�������ҵ��Ϣ\n";
    cout<<"   2.�����Զ�������ҵ��Ϣ\n";
    cout<<"   3.�˳�\n";
    cout<<"   ------------------------\n";
    cout<<"\n����������ѡ�Ĳ������:";
    string s, str;
    while (getline(cin, s)) {
        if (s == "1" || s == "2" || s == "3")
            break;
        else
            cout<<"�Ƿ�����,����������:";
    }
    if (s == "1") {
        cout<<"��������ҵ����:";
        while (getline(cin, str)) {
                int num = stoi(str);
                e = new node[num + 1];
                if (num == 0) {
                    cout<<"��ǰû����ҵ��Ҫ������\n";
                    break;
                }
                cout<<"�밴˳�����%d����ҵ�Ŀ�ʼʱ��ͽ���ʱ��\n", num;
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
                            cout<<"�Ƿ�����,����������:";
                    }
                }
                loading();
                check(num);
                break;
        }
    }
    else if (s == "2") {
        cout<<"�������Զ�������ҵ����:";
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
                    cout<<"��ǰû����ҵ��Ҫ������\n";
                    break;
                }
                cout<<"\n�Զ����ɵ���������:\n";
                for (int i = 0; i < k; i++)
                    printf("��%d����ҵ�Ŀ�ʼʱ����:%d,����ʱ����:%d\n", i + 1,
                        e[i].start, e[i].end);
                loading();
                check(k);
                break;
        }
    }
    cout<<"\nллʹ��\n";  //�������
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_INTENSITY | FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE);  //��������������Ϊ��ɫ
    return 0;
}
