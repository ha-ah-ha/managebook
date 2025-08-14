#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int main(){
    int n;
    cin>>n;
    int r=0,g=0,b=0;
    string str;
    cin>>str;
    for(int i=0;i<n;i++){

        if(str[i]=='R'){
            r++;
        }
        if(str[i]=='G'){
            g++;
        }
        if(str[i]=='B'){
            b++;
        }
    }
    cout<<min({r,g,b});
    return 0;
}