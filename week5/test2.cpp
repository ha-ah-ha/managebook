#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    if(n<26){
        cout<<-1;
        return 0;
    }

    int a[26]={0};
    for(int i=0;i<26;i++){
        a[i]=0;
    }
    int cnt=0,result=1000000;
    int l=0,r=0;
    //while()
    for(r=0;r<n;r++){
        int idx=str[r]-'A';
        if(a[idx]==0){
            cnt++;
        }
        a[idx]++;
        while(cnt==26){
            result=min(r-l+1,result);
            int leftidx=str[l]-'A';
            a[leftidx]--;
            if(a[leftidx]==0){
                cnt--;
            }
            l++;
        }
    }
    cout<<result;
}