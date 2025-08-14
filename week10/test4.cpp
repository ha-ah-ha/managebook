#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//树状数组类，用于高效处理前缀和及单点更新
class tree{
private:
    vector<ll> tree1; //存储树状数组的底层数据结构
public:
    tree(int size){
        tree1.resize(size+1,0); //初始化数组大小为size+1（树状数组下标从1开始）
    }
    //单点更新：在位置idx处增加delta
    void update(int idx,ll delta){
        while(idx<tree1.size()){
            tree1[idx]+=delta;
            idx+=idx&-idx; //移动到父节点
        }
    }
    //前缀和查询：计算从1到idx的元素和
    ll sum(int idx){
        ll result=0;
        while(idx>0){
            result+=tree1[idx];
            idx-=idx&-idx;//移动到前一个区间
        }
        return result;
    }
};

int main(){
    ll n;
    cin>>n;
    vector<pair<ll,ll>> v;//存储输入的程序的运行时间和内存占用
    vector<int> allm;//用于离散化所有内存占用
    
    //读取输入并收集所有程序信息
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        v.push_back({a,b});
        allm.push_back(v[i].second);
    }
    
    //离散化处理程序的内存占用
    sort(allm.begin(),allm.end());
    allm.erase(unique(allm.begin(),allm.end()),allm.end());
    int msize=allm.size();//离散化后的‘内存占用’数
    //以下称运行时间为x，内存占用为y
    //将点按x升序排序，x相同时按y升序排序（确保处理顺序正确）
    sort(v.begin(),v.end(),[](const pair<ll,ll>& a,const pair<ll,ll>& b){
        if(a.first!=b.first) return a.first<b.first;
        return a.second<b.second;
    });
    
    tree ft(msize);//初始化树状数组，用于统计y坐标分布
    vector<int> scores(n, 0);//统计每个得分的出现次数
    
    //遍历所有点，计算每个点的得分
    for(const auto& p:v){
        //获取当前y坐标的离散化后索引（从1开始）
        int midx=lower_bound(allm.begin(),allm.end(),p.second)-allm.begin()+1;
        //查询当前点左侧且y不大于当前点的点的数量即为得分
        int score=ft.sum(midx);
        scores[score]++;//记录该得分出现次数
        ft.update(midx,1);//将当前点的y坐标加入树状数组
    }
    
    //输出每个得分出现的次数
    for (int s : scores) {
        cout << s << "\n";
    }
    return 0;
}