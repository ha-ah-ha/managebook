#include<iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int** a=new int*[2];
    a[1]=new int[n];
    a[0]=new int[n];
    for(int i=0;i<n;i++){
        cin>>a[0][i]>>a[1][i];
    }
    for(int i=0;i<n;i++){
        int result=a[0][i]+a[1][i];
        cout<<result<<"\n";
    }
    return 0;
}