#include<iostream>
using namespace std;

int main(){
    int a,b;
    cin>>a>>b;
    int* c=new int[a];
    for(int i=0;i<a;i++)
        {cin>>c[i];}
    for(int i=0;i<a;i++){
        if(c[i]!=b){
            cout<<c[i]<<' ';
        }
    }
    return 0;
}