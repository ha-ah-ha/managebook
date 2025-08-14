#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n;
    ll h,x;
    cin>>n>>h>>x;
    vector<ll> y(n);
    vector<ll> z(n);
    for(int i=0;i<n;i++){
        cin>>y[i];
    }
    ll a;
    ll num=0;
    bool exsit=true;
    for(int i=0;i<n;i++){
        a=y[i]-x;   
        if(a<0){
            a=0;
        }
        h-=a;
        if(h>0){
            num++;
            x=max(x,y[i]);
        }
        else{
            exsit=false;
            break;
        }
    }
    if(exsit==true){
        cout<<"YES"<<"\n";
        cout<<h;
    }
    else{
        cout<<"NO"<<"\n";
        cout<<num;
    }
}   