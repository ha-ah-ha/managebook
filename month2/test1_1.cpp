#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define par pair<ll,ll>
ll n, num;
deque<par> q;
 
par topt = { 0,0 };
 
void init()
{
    num = 1;
    topt = { 0,0, };
    while(!q.empty()) q.pop_back();
}
 
void renew()
{
    if (topt.first == 0)//没有置顶
    {
        return;
    }
    else
    {
        for (ll i = 1; i <= q.size(); ++i)
        {
            if (topt.first == q.front().first)//找到了
            {
                q.front().second = topt.second;
            }
 
            if (!q.empty())
            {
                q.push_back(q.front());
                q.pop_front();
            }
        }
    }
}
 
void  add(ll u)//1.打开一个喜爱度为u的新窗口
{
    bool flag = true;
    for (ll i = 1; i <= q.size(); ++i)
    {
        if (q.front().first == u)
        {
            flag = false;
        }
        if (!q.empty())
        {
            q.push_back(q.front());
            q.pop_front();
        }
    }
    if (flag)//没有喜爱度为u的窗口，可以插入队列
    {
        q.push_back({ u, 0 });
        cout << "OpId #" << num << ": success." << endl;
    }
    else cout << "OpId #" << num << ": same likeness." << endl;
}
 
void close(ll u)//2.关掉一个喜爱度为u的窗口
{
    bool flag = true;
    ll c;//交流的话的数量
 
    for (ll i = 1; i <= q.size(); ++i)//遍历队列
    {
        if (u == q.front().first)//找到了
        {
            c = q.front().second;
            q.pop_front();
            flag = false;
            if (i > q.size()) break;
        }
        if (!q.empty())
        {
            q.push_back(q.front());
            q.pop_front();
        }
    }
    if (!flag)
    {
        if (u == topt.first)//关闭窗口处于置顶
        {
            topt.first = 0; topt.second = 0;
        }
        cout << "OpId #" << num << ": close " << u << " with " << c << "." << endl;
    }
    else cout << "OpId #" << num << ": invalid likeness." << endl;
 
}
 
void chat(ll w)//3.和顶层窗口交流w句话
{
    if (topt.first == 0)//没有置顶
    {
        if (!q.empty())
        {
            q.front().second += w;
            cout << "OpId #" << num << ": success." << endl;
        }
        else cout << "OpId #" << num << ": empty." << endl;
    }
    else//存在置顶窗口
    {
        topt.second += w;
        cout << "OpId #" << num << ": success." << endl;
        renew();//更新队列的值
    }
}
 
void rotate(ll x)//4.将第x个窗口放在队首
{
 
    if (x > q.size() || x < 1)//超出范围
    {
        cout << "OpId #" << num << ": out of range." << endl;
        return;
    }
    par te;
    for (ll i = 1; i <= q.size(); ++i)//遍历队列
    {
        if (i == x && (!q.empty()))//找到了第x个窗口
        {
            te = q.front();
            q.pop_front();
            if (i > q.size()) break;//如果是队列最后一个元素直接结束
        }
            q.push_back(q.front());
            q.pop_front();
    }
    q.push_front(te);
    cout << "OpId #" << num << ": success." << endl;
}
 
void prior()//5.将喜爱度最大的窗口放在队首
{
    if (q.empty())
    {
        cout << "OpId #" << num << ": empty." << endl;
        return;
    }
    ll maxf = 0;
    for (ll i = 1; i <= q.size(); ++i)//遍历找到最大喜爱度
    {
        if (q.front().first > maxf)
        {
            maxf = q.front().first;
        }
        q.push_back(q.front());
        q.pop_front();
    }
    par tem = { maxf,0 };
    for (ll i = 1; i <= q.size(); ++i)//将最大喜爱度的窗口提到队首
    {
        if (q.front().first == maxf)
        {
            tem.second = q.front().second;
            q.pop_front();
            if (i > q.size()) break;
        }
        if (!q.empty())
        {
            q.push_back(q.front());
            q.pop_front();
        }
    }
    q.push_front(tem);
    cout << "OpId #" << num << ": success." << endl;
}
 
void choose(ll u)//6.将喜爱度为u的放在队首
{
    bool flag = true;
    ll c;
    for (ll i = 1; i <= q.size(); ++i)
    {
        if (u == q.front().first)
        {
            c = q.front().second;
            flag = false;//找到喜爱度为u的窗口
            q.pop_front();
            if (i > q.size()) break;
        }
            q.push_back(q.front());
            q.pop_front();
    }
    if (flag)//没有喜爱度为u的窗口
    {
        cout << "OpId #" << num << ": invalid likeness." << endl;
    }
    else {
        q.push_front({ u,c });
        cout << "OpId #" << num << ": success." << endl;
    }
 
}
 
void top(ll u)//7.将喜爱度u的置顶
{
    bool flag = true;
    ll c;
    for (ll i = 1; i <= q.size(); ++i)//找到喜爱度为u的窗口
    {
        if (u == q.front().first)
        {
            c = q.front().second;
            flag = false;
        }
        q.push_back(q.front());
        q.pop_front();
    }
 
    if (flag)//没有找到
    {
        cout << "OpId #" << num << ": invalid likeness." << endl;
    }
    else//置顶
    {
        topt.first = u;
        topt.second = c;
        cout << "OpId #" << num << ": success." << endl;
    }
}
 
void untop()//8.取消置顶
{
    if (topt.first == 0)
    {
        cout << "OpId #" << num << ": no such person." << endl;
        return;
    }
    topt = { 0,0 };
    cout << "OpId #" << num << ": success." << endl;
}
void endt()
{
    bool flag = false;//初始无置顶
    ll tem = 0;//标记置顶窗口的喜爱度
    if (topt.first != 0)
    {
        tem = topt.first;
        if (topt.second != 0)
        {
            cout << "OpId #" << num << ": Bye " << topt.first << ": " << topt.second << "." << endl;
            num++;//
        }
        topt.first = 0;
        flag = true;//有置顶窗口
    }
    for (; !q.empty();)
    {
        if (flag && tem == q.front().first)//检测删除置顶窗口
        {
            q.pop_front();
            flag = false;
        }
        if(!q.empty()){
            if (q.front().second != 0)
            {
                cout << "OpId #" << num << ": Bye " << q.front().first << ": " << q.front().second << "." << endl;
                num++;//
            }
 
            q.pop_front();
        }
    }
}
 
int main()
{
 
    ll T;
    cin >> T;
    for (; T != 0; --T)
    {
        init();
        cin >> n;
        string logs;
        ll u;
        for (ll i = 1; i <= n; ++i)
        {
            cin >> logs;
            if (logs == "Add") { cin >> u; add(u); num++; }
            else if (logs == "Close") { cin >> u; close(u); num++; }
            else if (logs == "Chat") {
                cin >> u; chat(u); num++;
            }
            else if (logs == "Rotate") {
                cin >> u; rotate(u); num++;
            }
            else if (logs == "Prior") {
                prior(); num++;
            }
            else if (logs == "Choose") {
                cin >> u; choose(u); num++;
            }
            else if (logs == "Top") {
                cin >> u; top(u); num++;
            }
            else if (logs == "Untop") {
                untop(); num++;
            }
        }
        endt();
    }
    return 0;
}