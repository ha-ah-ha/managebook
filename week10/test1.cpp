#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll r,y,g;
    cin>>r>>y>>g;
    int n;
    cin>>n;
    ll result=0;
    for(int i=0;i<n;i++){
        int k;
        ll t;
        cin>>k>>t;
        if(k==0){
            result+=t;
        }
        else if(k==1){
            result+=t;
        }
        else if(k==2){
            result+=t+r;
        }
        else if(k==3){
            
        }
    }
    cout<<result;
}