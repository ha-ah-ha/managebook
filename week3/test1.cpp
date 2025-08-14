#include<iostream>
#include<queue>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    queue<int> q;
    for(int i=0;i<n;i++){
        q.push(i+1);
    }
    int i=1;
    while(q.size()>1){
        if(i%k==0||i%10==k){
            q.pop();
        }
        else{
            q.push(q.front());
            q.pop();
        }
        i++;
    }
    cout << q.front();
}

