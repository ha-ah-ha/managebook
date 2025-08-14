#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> a;
    int i=0,N=0;
    cin>>N;
    while(N!=0){
        int* b=new int[N];
        for(int j=0;j<N;j++){
            cin>>b[j];
        }
        int sum=0;
        for(int j=0;j<N;j++){
            sum+=b[j];
        }
        a.push_back(sum);
        cin>>N;
        i++;
    }
    for(int j=0;j<i;j++){
        cout<<a[j]<<"\n";
    }
}