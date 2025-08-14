#include<iostream>
#include<queue>
//#include<bits/stdc++.h>
using namespace std;

int main(){
    queue<int> result;
    while(true){ 
        queue<int> q;
        int n,a,b;
        cin>>n;
        if(n==0){
           break;
        }
        cin>>a>>b;
        if(a==0||b==0){
            break;
        }
        int* operation=new int[n+1];
        for(int i=0;i<n;i++){
            operation[i+1]=-1;
        }
        int* k=new int[n+1];
        for(int i=0;i<n;i++){
            cin>>k[i+1];
            if(k[i+1]==0){
                delete[] operation;
                delete[] k;
                break;
            }
        }
        q.push(a);
        operation[a]=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=-1;i<=1;i+=2){
                int v=u+k[u]*i;
                if(v>=1&&v<=n&&operation[v]==-1){
                    q.push(v);
                    operation[v]=operation[u]+1;
                }
            }
        }
        result.push(operation[b]);
        delete[] operation;
        delete[] k;
    }
    while(!result.empty()){
        cout<<result.front()<<"\n";
        result.pop();
    }
    return 0;
}