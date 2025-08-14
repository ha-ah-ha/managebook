#include<iostream>
#include<string>
#include<set>
using namespace std;

int main(){
    int n;
    cin>>n;
    for(int j=0;j<n;j++){
        string str;
        bool big=false;
        set<char> s;
        cin>>str;
        bool r=true;
        if(str.size()<26){
            cout<<"yes"<<"\n";
            r=false;
        }
        if(r==true){
            for(int i=0;i<str.size();i++){
                // if(str[i]==str[i+1]){
                //     cout<<"yes"<<"\n";
                //     r=false;
                //     break;
                // // return 0;
                // }
                if(str.back()<=90&&str.back()>=65){
                    s.insert(str[i]+32);
                    big=true;
                }
                if(str.back()<='z'&&str.back()>='a'){
                    s.insert(str[i]);
                }
            }
        }
        
        if(r==true&&big==true){
            // if(!((str.back()<='z'&&str.back()>='a')||(str.back()<='Z'&&str.back()>='A'))){
            //     cout<<"yes"<<"\n";
            //     //return 0;
            // }
            if(s.size()<26){
                cout<<"yes"<<"\n";
                
            }
            else {
                cout<<"no"<<"\n";
            }
        }
    }
}