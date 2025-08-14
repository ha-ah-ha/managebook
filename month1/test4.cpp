#include<iostream>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    int* q=new int[k+1];
    for(int i=1;i<k+1;i++){
        q[i]=0;
    }
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        q[a]++;

    }
    int num=0;
    for(int i=1;i<=k;i++){
        while(q[i]>=2){
            q[i]-=2;
            num++;
        }
    }
    cout<<num;
}