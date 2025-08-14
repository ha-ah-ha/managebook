#include<iostream>
using namespace std;

int main(){
    int a=0; 
    cin>>a;
    int* b=new int[a];
    int* c=new int[a];
    for(int i=0;i<a;i++){
        cin>>b[i];
    }
    for(int i=0;i<a;i++)
    {   cin>>c[i];}
    int sum=0;
    for(int i=0;i<a;i++){
        sum+=b[i]*c[i];
    }
    if(sum==0){
        cout<<"Yes";
        delete[] b;
        delete[] c;
        return 0;
    }
    delete[] b;
    delete[] c;
    cout<<"No";
    return 0;
}