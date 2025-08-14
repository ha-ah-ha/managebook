#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    string result="";
    bool lianxu=false;
    for(int i=0;i<n;i++){
        if(lianxu==false){
            result+=str[i];
            if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'){
                lianxu=true;
            }
            continue;
        }
        if(!(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u')){
            lianxu=false;
            result+=str[i];
        }
        
    }
    cout<<result;
}