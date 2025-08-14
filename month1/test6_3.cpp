#include<bits/stdc++.h>
using namespace std;

int main(){
    long long l,r,k;
    cin>>l>>r>>k;
    bool found=false;
    long long ans=1;
    if(k==1){
        if(l==1){
            cout<<1;
            return 0;
        }
        else {
            cout<<-1;
            return 0;
        }
    }
    else{
        while(ans<l&&ans<=r/k){
            ans*=k;
        }
        while(ans>=l&&ans<=r){
            cout<<ans<<" ";
            found=true;
            if(ans>r/k){
                break;
            }
            ans*=k;
        }
    }
    if(!found){
        cout<<-1<<endl;
        
    }
}