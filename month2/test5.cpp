#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n;
    cin>>n;
    vector<ll> a(n);
    ll num=0;
    for(int i=0;i<n;i++){
        ll b;
        cin>>b;
        a[i]=b;
        num+=b;
    }
    ll ans=0;
    ll pi=0;
    ll newnum=0;
    bool used=false;
    for(int i=0;i<n;i++){
        newnum+=a[i];
        num-=a[i];
        for(int j=0;j<a[i];j++){
            ans+=pi+1;
            pi++;
        }
        if(newnum>=num&&!used){
            pi=0;
            used=true;
        }
    }
    cout<<ans;
}