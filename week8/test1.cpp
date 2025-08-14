#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        int value;
        cin>>value;
        v[i]=value;
    }
    vector<int> newv(n);
    newv[0]=(v[0]+v[1])/2;
    newv[n-1]=(v[n-1]+v[n-2])/2;
    for(int i=1;i<=n-2;i++){
        newv[i]=(v[i-1]+v[i]+v[i+1])/3;
    }
    for(int i=0;i<n;i++){
        cout<<newv[i]<<' ';
    }
}