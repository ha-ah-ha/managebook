#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    long long price=100000;
    int num=0;
    for(int i=1;i<n+1;i++){
        int pri;
        cin>>pri;
        string str;
        cin>>str;
        int zero=0,one=0,five=0;
        for(int j=0;j<str.size();j++){
            if(str[j]=='0'&&zero<2){
                zero++;
            }
            else if(str[j]=='1'&&one<1){
                one++;
            }
            else if(str[j]=='5'&&five<1){
                five++;
            }
            if(zero==2&&five==1&&one==1){
                if(pri<price){
                    price=pri;
                    num=i;
                }
                break;
            }
        }
    }
    cout<<num;
    return 0;
}