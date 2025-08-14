#include<bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    int x,y;
    cin>>n>>x>>y;
    long long maxtime=(n-1)*min(x,y);
    long long mintime=(n-1)/(x+y);
    long long mid;
    while(1){
        mid=(maxtime+mintime)/2;
        if(mid==mintime){
            break;
        }
        long long num=mid/x+mid/y;
        if(num>=n-1){
            maxtime=mid;
        }
        else{
            mintime=mid;
        }
    }
    cout<<maxtime+min(x,y);
}