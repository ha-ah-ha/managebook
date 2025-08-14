#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> a;
    int b=0,c=0;
    while(cin>>b>>c){
        a.push_back(b+c);
    }
    int i=0;
    while(!a.empty()){
        cout<<a[i++]<<"\n";
        a.pop_back();
    }
}