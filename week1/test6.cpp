#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

int fun(int* location,int n,int p){
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=pow(location[i]-p,2);
    }
    return sum;
}

int main(){
    int n;
    cin>>n;
    int* location=new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>location[i];
    }
    int min1=*min_element(location,location+n);
    int max1=*max_element(location,location+n);
    int minp=fun(location,n,min1);
    for(int i=min1+1;i<max1;i++){
        int newmin=fun(location,n,i);
        if(newmin<minp){
            minp=newmin;
        }
    }
    cout<<minp;
    delete[] location;
    return 0;
}