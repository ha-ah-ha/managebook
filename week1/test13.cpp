#include<iostream>
using namespace std;

int main(){
    int N=0;
    cin>>N;
    int* a=new int[N];
    for(int i=0;i<N;i++){
        int M=0;
        cin>>M;
        int sum=0,sum1=0;
        for(int j=0;j<M;j++){
            cin>>sum1;
            sum+=sum1;
        }
        a[i]=sum;
    }
    for(int i=0;i<N;i++){
        cout<<a[i]<<"\n";
    }
    return 0;
}