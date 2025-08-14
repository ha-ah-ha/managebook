#include<iostream>
#include<queue>
#include<string>
#include<istream>
using namespace std;

int main(){
    int n;
    queue<char> q;
    string str;
    getline(cin,str);
    // while(cin>>n){
    //     q.push(n);
    // }
    for(int i=0;i<str.size();i++){
       if(str[i]!=' '){q.push(str[i]);}
    }
    int center=1;
    int num=0;
    while(q.front()!='0'){
        if(q.front()=='1'){
            num++;
            center=1;
        }
        else if(q.front()=='2'){
            num=num+2*center;
            center++;
        }
        q.pop();
    }
    cout<<num;
}