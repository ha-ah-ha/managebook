#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> a;
    int M=0;
    while(cin>>M){
        int sum=0,sum1=0;
        for(int i=0;i<M;i++){
            cin>>sum1;
            sum+=sum1;
        }
        a.push_back(sum);
    }
    for(int i=0;i<a.size();i++){
        cout<<a[i]<<"\n";
    }
    return 0;
}