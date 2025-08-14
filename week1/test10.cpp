#include<iostream>
using namespace std;

int main(){
    int a,b;
    cin>>a>>b;
    int c[100000]={0};
    int i=0;
    while(a!=0&&b!=0){
        c[i++]=a+b;
        cin>>a>>b;
    }
    for(int j=0;j<i;j++){
        cout<<c[j]<<"\n";
    }
    return 0;
}