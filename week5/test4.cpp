#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<long long> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    stack<int> s;
    long long maxarea=0;
    a.push_back(0);
    for(int i=0;i<a.size();++i){
        while(!s.empty()&&a[i]<a[s.top()]){
            int height=a[s.top()];
            s.pop();
            long long width=0;
            if(s.empty()){
                width=i;
            }
            else{
                width=i-s.top()-1;
            }
            maxarea=max(maxarea,height*width);
        }
        s.push(i);
    }
    cout<<maxarea;
}