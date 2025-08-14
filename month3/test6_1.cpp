#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> v(200000,0);
    vector<int> a(n+1,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int num=0;
    for(int i=n-1;i>=0;i--){
        if(v[a[i]]==0){
            v[a[i]]=1;
            num++;
        }
        else{
            break;
        }
    }
    num=n-num;
    cout<<num;
}