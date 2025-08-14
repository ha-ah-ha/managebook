#include<iostream>
#include<cstdio>
using namespace std;

int main(){
    long int a=0,b=0;
    cin>>a>>b;
    double c=1.000*(a-b)/a*100;
    printf("%.3f\n",c);
}