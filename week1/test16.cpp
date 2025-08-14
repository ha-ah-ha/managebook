#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

int main(){
    string line;
    vector<int> c;
    while(getline(cin,line)){
        stringstream ss(line);
        int a,b;
        ss>>hex>>a>>hex>>b;
        c.push_back(a+b);
    }
    for(int i=0;i<c.size();i++){
        cout<<c[i]<<"\n";
    }
    return 0;
}