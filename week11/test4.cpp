#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    vector<int> tails;
    for(int x:a){
        auto it=lower_bound(tails.begin(),tails.end(),x);
        if(it==tails.end()){
            tails.push_back(x);
        }
        else{
            *it=x;
        }
    }
    cout<<tails.size()<<endl;
}