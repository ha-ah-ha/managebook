#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n;
    cin>>n;
    deque<ll> q(n);
    ll sum=0;
    for(int i=0;i<n;i++){
        ll a;
        cin>>a;
        q[i]=a;
        sum+=a;
    }
    int newsum=0;
    int num=0;
    for(int i=0;i<n;i++){
        newsum+=q[i];
        sum-=q[i];
        if(sum==newsum){
            num++;
        }
    }
    cout<<num-1;
}