#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    unordered_map<int,ll> sum;
    for(int num:a){
        sum[num]+=num;
    }
    vector<int> nums;
    for(auto& p:sum){
        nums.push_back(p.first);
    }
    sort(nums.begin(),nums.end());
    ll pre=0,pre1=0;
    int prenum=-2;
    for(int it:nums){
        if(it==prenum+1){
            ll cur=max(pre+sum[it],pre1);
            pre=pre1;
            pre1=cur;
        }
        else{
            ll cur=pre1+sum[it];
            pre=pre1;
            pre1=cur;
        }
        prenum=it;
    }
    cout<<pre1<<endl;
}