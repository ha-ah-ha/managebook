#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int num=0;
        int a[3];
        for(int j=0;j<3;j++){
            cin>>a[j];
            num+=a[j];
         //   cout<<a[i];
        }
        int c=num/9;
        if(num%9==0){
            bool is=false;
            for(int j=0;j<3;j++){
                if(a[j]<c){
                    cout<<"NO"<<"\n";
                    is=true;
                    break;
                }
            }
            if(is==false){cout<<"YES"<<"\n";}
        }
        else{
            cout<<"NO"<<"\n";
        }
    }
}