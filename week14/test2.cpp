#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int n,m;
    cin>>n>>m;
    vector<ll> pre(n+1,0);
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        pre[i]=pre[i-1]+a;
    }
    deque<int> dq;
    ll maxsum=0;
    for(int i=1;i<=n;i++){
        while(!dq.empty()&&dq.front()<i-m){
            dq.pop_front();
        }
        while(!dq.empty()&&pre[dq.back()]>=pre[i]){//维护单调递增队列
            dq.pop_back();
        }
        dq.push_back(i);
        if(pre[i]-pre[dq.front()]>maxsum){
            maxsum=pre[i]-pre[dq.front()];
        }
        if(dq.front()==0&&pre[i]>maxsum){
            maxsum=pre[i];
        }
    }
    cout<<maxsum;
    return 0;
}