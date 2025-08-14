#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll num=1;
deque<pair<ll,ll>> q;
pair<ll,ll> top={0,0};

// void init(){
//     while(!q.empty()){
//         q.pop_back();
//     }
//     top={0,0};
//     num=1;
// }

void add(ll u){
    //bool find=false;
    for(ll i=0;i<q.size();i++){
        if(q[i].first==u){
            cout<<"OpId #"<<num<<": same likeness.\n";
            return;
        }
    }
    q.push_back({u,0});
    cout<<"OpId #"<<num<<": success.\n";
}
void close(ll u){
    bool found = false;
    for (auto it = q.begin(); it != q.end();) {
        if (it->first == u) {
            it = q.erase(it);  // erase 返回下一个元素的迭代器
            found = true;
        } else {
            ++it;
        }
    }
    if (found) {
        cout << "OpId #" << num << ": success.\n";
    } else {
        cout << "OpId #" << num << ": invalid likeness.\n";
    }
}
void chat(ll w){
    if(q.empty()){
        cout<<"OpId #"<<num<<": empty.\n";
        return;
    }
    else{
        if(top.first==0){
            cout<<"OpId #"<<num<<": success.\n";
            q.front().second+=w;
        }
        else{
            top.second+=w;
            for(ll i=0;i<q.size();i++){
                if(q[i].first==top.first){
                    q[i].second+=w;
                    break;
                }
            }
        }
    }
}
void rotate(ll x){
    if(x>q.size()||x<1){
        cout<<"OpId #"<<num<<": out of range.\n";
        return;
    }
    else{
        pair<ll,ll> t={q[x-1].first,q[x-1].second};
        q.erase(q.begin()+x-1);
        q.push_front(t);
        cout<<"OpId #"<<num<<": success.\n";
        return;
    }
}
void prior(){
    if(q.empty()){
        cout<<"OpId #"<<num<<": empty.\n";
        return;
    }
    auto max_it=max_element(q.begin(),q.end(),[](const auto& a,const auto& b){
        return a.first<b.first;
    });

    for(auto it=q.begin();it!=q.end();){
        if(it->first==max_it->first){
            pair<ll,ll> t=*(it);
            q.erase(it);
            q.push_front(t);
            cout<<"OpId #"<<num<<": success.\n";
            //break;
            return;
        }
        ++it;
    }
}

void choose(ll u)
{
    bool flag = true;
    ll c;
    ll original_size = q.size();
    for (ll i = 0; i < original_size; ++i) {
        auto current = q.front();
        q.pop_front();
        if (current.first == u && flag) {
            c = current.second;
            flag = false;
        } else {
            q.push_back(current);
        }
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
 
void top1(ll u)//7.将喜爱度u的置顶
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
        top.first = u;
        top.second = c;
        cout << "OpId #" << num << ": success." << endl;
    }
}
 
void untop()//8.取消置顶
{
    if (top.first == 0)
    {
        cout << "OpId #" << num << ": no such person." << endl;
        return;
    }
    top = { 0,0 };
    cout << "OpId #" << num << ": success." << endl;
}
void endt()
{
    bool flag = false;//初始无置顶
    ll tem = 0;//标记置顶窗口的喜爱度
    if (top.first != 0)
    {
        tem = top.first;
        if (top.second != 0)
        {
            cout << "OpId #" << num << ": Bye " << top.first << ": " << top.second << "." << endl;
            num++;//
        }
        top.first = 0;
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
                //num++;//
            }
 
            q.pop_front();
        }
    }
}
int main(){
    int t;
    cin>>t;
    
    while(t--){
        ll n;
        cin>>n;
        q.clear();
    top={0,0};
    num=1;
        for(ll i=0;i<n;i++){
            string order;
            cin>>order;
            if(order=="Add"){
                ll u;
                cin>>u;
                add(u);
                num++;
            }
            else if(order=="Close"){
                ll u;
                cin>>u;
                close(u);
                num++;
            }
            else if(order=="Chat"){
                ll w;
                cin>>w;
                chat(w);
                num++;
            }
            else if(order=="Rotate"){
                ll x;
                cin>>x;
                rotate(x);
                num++;
            }
            else if(order=="Prior"){
                prior();
                num++;
            }
            else if(order=="Choose"){
                ll u;
                cin>>u;
                choose(u);
                num++;
            }
            else if(order=="Top"){
                ll u;
                cin>>u;
                top1(u);
                num++;
            }
            else if(order=="Untop"){
                untop();
                num++;
            }
        }
        endt();
    }
    return 0;
}