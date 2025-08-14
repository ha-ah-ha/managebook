#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n;
    cin>>n;//n个区间
    map<ll,int> m;//用来存放各个时间点对应的标记次数
    for(int i=0;i<n*2;i++){
        ll l,r;
        cin>>l>>r;//输入区间
        for(ll j=l;j<r;j++){//从l到r，因为输入的l、r分别是区间的左右端点，而不是区间的编号
            //所以在标记的时候要标记区间而不是区间端点，所以只标记l到r-1.
            m[j]++;//在m中对应时间点标记次数+1
        }
    }
    int num=0;//记录时间
    for(auto& [pos,val] : m){//遍历所有被标记的时间点
        if(val==2){//如果被标记了两次
            num++;//时间+1
        }
    }
    cout<<num;
}