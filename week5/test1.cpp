#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    vector<int> pos[26];
    for(int i=0;i<n;i++){
        int c=str[i]-'A';
        pos[c].push_back(i+1);
    }
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        if((r-l)<25){
            cout<<"NO"<<"\n";
            continue;
        }
        else{
            bool ok=true;
            for(int k=0;k<26;k++){
                if(pos[k].empty()){
                    ok=false;
                    break;
                }
                auto it = lower_bound(pos[k].begin(), pos[k].end(), l);
                if(it==pos[k].end()||*it>r){
                    ok=false;
                    break;
                }
            }
            if(ok==true){
                cout<<"YES"<<"\n";
            }
            else{
                cout<<"NO"<<"\n";
            }

        }
    }
}