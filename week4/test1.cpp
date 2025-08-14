#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    double * a=new double[n];
    double sumrop=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
        sumrop+=a[i];
    }
    sort(a,a+n);
    double maxrope=sumrop/k;
    double minrope=a[0]/k;
    double mid=0;
    while(1){
        mid=(maxrope+minrope)/2;
        int cnt=0;
        for(int i=0;i<n;i++){
            cnt+=a[i]/mid;
        }
        if(cnt>=k){
            minrope=mid;
        }
        else{
            maxrope=mid;
        }
        if((maxrope-minrope)<=1e-6){
            break;
        }
    }
    cout<<mid<<endl;
    return 0;
}