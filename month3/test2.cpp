#include<bits/stdc++.h>
using namespace std;
class task;
class factory;
vector<task> tname;//任务数组
vector<string> fname;//车间名字
static unsigned int p = 1;
int myrand(void)
{
    p = p * 1103515245 + 12345;
    return((unsigned int)(p / 65536) % 100);
}

class task//任务
{
public:
    task() {}
    task(string n, long long b, long long r, int i) :name(n), begin(b), run(r), index(i) {}
    string name;//名字
    long long begin;//开始添加时间
    long long run;//运行时间
    long long end = 0;//结束时间
    int index;//添加任务的序号
};

struct cmp1
{
    bool operator()(task& t1, task& t2)//运行时间小的优先，相同则字典序大的优先
    {
        if (t1.run == t2.run)
            return t1.name < t2.name;
        return t1.run > t2.run;
    }
};

struct cmp2
{
    bool operator()(task& t1, task& t2)//运行时间大的优先，相同则字典序大的优先
    {
        if (t1.run == t2.run)
            return t1.name < t2.name;
        return t1.run < t2.run;
    }
};

bool cmp3(task& t1, task& t2)//最后任务完成输出顺序的排序
{
    if (t1.end == t2.end)
        return t1.index < t2.index;
    return t1.end < t2.end;
}

class factory//车间
{
public:
    factory() {}
    factory(long long c, string n, string t) :curtime(c), name(n), type(t) {}
    long long curtime;//现在的时间
    string name;//名字
    string type;//类别，TF、SF、LF
    queue<task> q1;//TF，先来先服务
    priority_queue<task, vector<task>, cmp1> q2;//SF，短的优先
    priority_queue<task, vector<task>, cmp2> q3;//LF，长的优先

    void deal(task& job)
    {
        if (curtime < job.begin)//如果当前车间的空闲时间比任务开始时间早
        {
            job.end = job.begin + job.run;
            curtime = job.end;//空闲时间更新为完成该任务的时间
        }
        else//如果更晚
        {
            job.end = curtime + job.run;//等到空闲再运行该任务
            curtime = job.end;
        }
        tname[job.index] = job;
        return;
    }

    void dealpush(task& job)
    {
        if (type == "TF")
        {
            if (q1.empty() == true)//队列为空
            {
                if (curtime < job.begin)//车间空闲，加入队列
                {
                    deal(job);
                }
                else//车间不空闲，加入队列
                {
                    q1.push(job);
                }
            }
            else///队列不为空
            {
                while (curtime <= job.begin && q1.empty() == false)//将该任务之前的所有能执行的任务先执行了
                {
                    auto temp = q1.front();
                    q1.pop();
                    deal(temp);
                }
                q1.push(job);
            }
        }
        if (type == "SF")
        {
            if (q2.empty() == true)//队列为空
            {
                if (curtime < job.begin)//车间不空闲，加入队列
                {
                    deal(job);
                }
                else
                {
                    q2.push(job);
                }
            }
            else///队列不为空
            {
                while (curtime <= job.begin && q2.empty() == false)//将该任务之前的所有能执行的任务先执行了
                {
                    auto temp = q2.top();
                    q2.pop();
                    deal(temp);
                }
                q2.push(job);
            }
        }
        if (type == "LF")
        {
            if (q3.empty() == true)//队列为空
            {
                if (curtime < job.begin)//车间不空闲，加入队列
                {
                    deal(job);
                }
                else
                {
                    q3.push(job);
                }
            }
            else///队列不为空
            {
                while (curtime <= job.begin && q3.empty() == false)//将该任务之前的所有能执行的任务先执行了
                {
                    auto temp = q3.top();
                    q3.pop();
                    deal(temp);
                }
                q3.push(job);
            }
        }
    }

    void dealrest()//车间对队列中的任务进行处理
    {
        //三选一
        if (type == "TF")
        {
            while (!q1.empty())
            {
                auto job = q1.front();
                q1.pop();
                deal(job);
            }
            return;
        }
        else if (type == "SF")
        {
            while (!q2.empty())
            {
                auto job = q2.top();
                q2.pop();
                deal(job);
            }
            return;
        }
        else if (type == "LF")
        {
            while (!q3.empty())
            {
                auto job = q3.top();
                q3.pop();
                deal(job);
            }
            return;
        }
    }
};



int main()
{
    int n, m;
    cin >> n >> m;
    tname.resize(m);//任务数组
    fname.resize(n);//车间名字
    unordered_map<string, factory> rooms;//车间名字和车间类对象的映射

    for (int i = 0; i < n; i++)
    {
        string t_name, t_type;
        cin >> t_name >> t_type;
        fname[i] = t_name;
        factory temp(0, t_name, t_type);
        rooms.insert({ t_name, temp });
    }
    for (int i = 0; i < m; i++)
    {
        long long t, d, k;
        string s;
        cin >> t >> s >> d >> k;
        task temp(s, t, d, i);
        tname[i] = temp;
        bool flag = false;
        vector<string> arr(k);
        for (int j = 0; j < k; j++)
        {
            cin >> arr[j];
        }
        for (int j = 0; j < k; j++)
        {
            string str = arr[j];
            if (flag == true)
                continue;
            if (j == k - 1 || (100 / k) > myrand())//进入该车间，千万别改这一行的算式的前后顺序，不然褒姒的 
            {
                rooms[str].dealpush(tname[i]);
                flag = true;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        string name = fname[i];
        rooms[name].dealrest();
    }
    sort(tname.begin(), tname.end(), cmp3);
    for (int i = 0; i < m; i++)
    {
        cout << tname[i].end << " " << tname[i].name << "\n";
    }
    return 0;
}