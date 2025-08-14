#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    int ans=1;
    int d=0;
    for(int i=0;i<n;i++){
        if(str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'){
            str[i]='a';
        }
    }
    for(int i=1;i<n;i++){
        d=0;
        if(str[i]==str[i-1]){
            d=2;
            int l=min(i-1,n-i-1);
            for(int j=0;j<l;j++){
                if(str[i-2-j]==str[i+1+j]){
                    d+=2;
                }
                else{
                    break;
                }
            }
            if(d>ans){
                ans=d;
            }
        }
        d=1;
        int l=min(i,n-1-i);
        for(int j=0;j<l;j++){
            if(str[i-j-1]==str[i+1+j]){
                d+=2;
            }
            else{
                break;
            }
        }
        if(d>ans){
            ans=d;
        }
    }
    cout<<ans;
}