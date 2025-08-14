#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    int count=0;
    int maxcount=0;
    for(int i=0;i<n;i++){
        if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'){
            count++;
        }
        else{
            if(count>maxcount){
                maxcount=count;
            }
            count=0;
        }
    }
    cout<<maxcount;
}