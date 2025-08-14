#include<iostream>
#include<string>
using namespace std;

int main(){
    string str;
    getline(cin,str);
    int i=0,j=1;
    //bool is=true;
    while(i<str.size()&&j<str.size()){
        if(!(str[i]<=122&&str[i]>=97&&str[j]<=90&&str[j]>=65)){
            cout<<"No";
            return 0;
        }
        i+=2;
        j+=2;
    }
    cout<<"Yes";
    return 0;
}