#include<iostream>
using namespace std;

long long g1(long long x){//降序
    int a[10]={0};
    int i=0;
    while(x>0){
        a[i++]=x%10;
        x/=10;
    }
    long long result=0;
    for(int k=0;k<i-1;k++){
        for(int j=0;j<i-1-k;j++){
            if(a[j]<a[j+1]){
                int b=a[j];
                a[j]=a[j+1];
                a[j+1]=b;
            }
        }
    }
    for(int j=0;j<i;j++){
        result=result*10+a[j];
    }
    return result;
}

long long g2(long long x){//升序
    int a[10];
    int i=0;
    while(x>0){
        a[i++]=x%10;
        x/=10;
    }
    for(int k=0;k<i-1;k++){
        for(int j=0;j<i-1-k;j++){
            if(a[j]>a[j+1]){
                int b=a[j];
                a[j]=a[j+1];
                a[j+1]=b;
            }
        }
    }
    long long result=0;
    for(int k=0;k<i;k++){
        if(a[k]!=0){
        result=result*10+a[k];}
    }
    return result;
}

long long fun(long long x1,long long x2){
    return x1-x2;
}

int main(){
    long long N=0,K=0;
    cin>>N>>K;
    int i=0;
    long long x1=g1(N);
    long long x2=g2(N);
    long long a=fun(x1,x2);
    while(i<K-1){
        x1=g1(a);
        x2=g2(a);
        a=fun(x1,x2);
        i++;
    }
    cout<<a;
    return 0;
}