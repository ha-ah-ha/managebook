#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

int main(){
    vector<int> a;
    string line;
    while(getline(cin,line)){
        stringstream ss(line);
        int sum=0,num;
        while(ss>>num){
            sum+=num;
        }
        a.push_back(sum);
    }
    for(int i=0;i<a.size();i++){
        cout<<a[i]<<"\n";
    }
    return 0;
}