#include<iostream>
#include<string>
#include <windows.h>
#include<random>
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

void loading() {//数据处理进度条
    cout<<"\n数据处理中,请稍后……\n";
    for (int i = 1; i <= 5; i++) {
        cout<<"[";
        for (int j = 1; j <= i; j++) cout<<"■■";
        for (int j = 0; j < 5 - i; j++) cout<<"□□";
        printf("]\t%d%%", i * 20);
        Sleep(1000);
        cout<<"\r";
    }
    cout<<"\n\n";
    return;
}

void loading2() {//打印数据处理进度条
    cout<<"\n数据生成中,请稍后……\n";
    for (int i = 1; i <= 2; i++) {
        cout<<"[";
        for (int j = 1; j <= i; j++) cout<<"■■■■■";
        for (int j = 0; j < 2 - i; j++) cout<<"□□□□□";
        printf("]\t%d%%", i * 50);
        Sleep(1000);
        cout<<"\r";
    }
    cout<<"\n\n";
    return;
}

int heapsize = 0;//最小堆中作业个数

void insert(int x, int k) {//插入最小堆
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
void renew(int u) {//更新最小堆
    int t = u;
    if (2 * u <= heapsize && h[2 * u].w < h[t].w) t = 2 * u;
    if (2 * u + 1 <= heapsize && h[2 * u + 1].w < h[t].w) t = 2 * u + 1;
    if (t != u) {
        swap(h[t], h[u]);
        renew(t);
    }
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

void check(int k)//调度核心函数
{
    int ans = 1;//调度序号计数器
    sort(e, e + k, cmp);//按开始时间排序所有作业
    int flag = 0;//CPU占用标志（0为空闲）
    int time=0;//当前调度结束时间
    int a = 0;
    for (int i = 1; i <= 2000; i++) {//模拟时间流逝（1~2000时间单位）
        if (i == time) flag = 0;//检查当前时间是否完成前一个调度
        for (int j = 0; j < k; j++)
        {
            if (e[j].start == i)
            {
                insert(e[j].end, j);//将当前时间到达的作业插入堆
                a++;
            }
            /*else {
                break;
            }*/
        }
        if (heapsize > 0) {//处理当前可调度作业
            if (flag == 0) {//空闲时进行调度
                int tot = h[1].num;
                int weight = h[1].w;
                swap(h[1], h[heapsize]);
                heapsize--;
                renew(1);
                time = i + e[tot].end - e[tot].start;
                printf("%d-编号为%d的作业于%d时进入队列\t于%d时开始调度\t于%d时离开\t调度时长为%d\t等待时间%d\t优先数动态变化%d -> %d\n",
                    ans++, e[tot].num, e[tot].start, i,
                    i + e[tot].end - e[tot].start, e[tot].end - e[tot].start,
                    e[tot].wait,e[tot].end-e[tot].start, e[tot].end - i);
                flag = 1;//标记有作业正在调度
                
            }
            for (int idx = 1; idx <= heapsize; idx++) {
                e[h[idx].num].wait=i- e[h[idx].num].start;//更新等待时间
                h[idx].w = (e[h[idx].num].end - e[h[idx].num].start) - e[h[idx].num].wait;//更新有心啊及
            }
        }
    }
    return;
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
    cout<<"\n***************************************************\n";  //输出文字信息
    cout<<"*         -基于优先队列的作业调度算法实现-        *\n";
    cout<<"*                   -最小堆实现-                  *\n";
    cout<<"***************************************************\n\n";
    cout<<"\n----------字体颜色----------\n";
    cout<<"0.白色\n";
    cout<<"1.红色\n";
    cout<<"2.绿色\n";
    cout<<"3.蓝色\n";
    cout<<"4.粉色\n";
    cout<<"5.青色\n";
    cout<<"6.黄色\n";
    cout<<"7.随机生成\n";
    cout<<"-----------------------------\n";
    cout<<"\n请输入您想用字体颜色的编号:";
    string tmp;
    while (getline(cin, tmp)) {
        if (tmp == "0" || tmp == "1" || tmp == "2" || tmp == "3" ||
            tmp == "4" || tmp == "5" || tmp == "6" || tmp == "7") {
            color(stoi(tmp));
            break;
        }
        else
            cout<<"非法输入,请重新输入:";
    }

    cout<<"\n   ----------菜单----------\n";
    cout<<"   1.手动输入作业信息\n";
    cout<<"   2.电脑自动生成作业信息\n";
    cout<<"   3.退出\n";
    cout<<"   ------------------------\n";
    cout<<"\n请输入您所选的操作编号:";
    string s, str;
    while (getline(cin, s)) {
        if (s == "1" || s == "2" || s == "3")
            break;
        else
            cout<<"非法输入,请重新输入:";
    }
    if (s == "1") {
        cout<<"请输入作业个数:";
        while (getline(cin, str)) {
                int num = stoi(str);
                e = new node[num + 1];
                if (num == 0) {
                    cout<<"当前没有作业需要被调度\n";
                    break;
                }
                cout<<"请按顺序给出%d个作业的开始时间和结束时间\n", num;
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
                            cout<<"非法输入,请重新输入:";
                    }
                }
                loading();
                check(num);
                break;
        }
    }
    else if (s == "2") {
        cout<<"请输入自动生成作业个数:";
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
                    cout<<"当前没有作业需要被调度\n";
                    break;
                }
                cout<<"\n自动生成的数据如下:\n";
                for (int i = 0; i < k; i++)
                    printf("第%d个作业的开始时间是:%d,结束时间是:%d\n", i + 1,
                        e[i].start, e[i].end);
                loading();
                check(k);
                break;
        }
    }
    cout<<"\n谢谢使用\n";  //程序结束
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_INTENSITY | FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE);  //将字体重新设置为白色
    return 0;
}
