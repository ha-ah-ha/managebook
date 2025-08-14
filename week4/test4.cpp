#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    long long* a=new long long[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    int cnt=0;
    for(int i=0;i<n-1;i++){
        if((a[i+1]-a[i])<=k){
            cnt++;
        }
    }
    cout<<cnt;
    return 0;
}