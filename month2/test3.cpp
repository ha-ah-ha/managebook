#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<ll>> e(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ll a;
            cin>>a;
            e[i].push_back(a);
        }
    }
    int num=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(m>1&&n>1){
                if(i==0){
                if(j==0){
                    if(e[i][j+1]<e[i][j]&&e[i+1][j]<e[i][j]){
                        num++;
                    }
                }
                else if(j==m-1){
                    if(e[i][j-1]<e[i][j]&&e[i+1][j]<e[i][j]){
                        num++;
                    }
                }
                else{
                    if(e[i][j+1]<e[i][j]&&e[i+1][j]<e[i][j]&&e[i][j-1]<e[i][j]){
                        num++;
                    }
                }
            }
            else if(i==n-1){
                if(j==0){
                    if(e[i][j+1]<e[i][j]&&e[i-1][j]<e[i][j]){
                        num++;
                    }
                }
                else if(j==m-1){
                    if(e[i][j-1]<e[i][j]&&e[i-1][j]<e[i][j]){
                        num++;
                    }
                }
                else{
                    if(e[i][j+1]<e[i][j]&&e[i-1][j]<e[i][j]&&e[i][j-1]<e[i][j]){
                        num++;
                    }
                }
            }
            else{
                if(j==0){
                    if(e[i][j+1]<e[i][j]&&e[i-1][j]<e[i][j]&&e[i+1][j]<e[i][j]){
                        num++;
                    }
                }
                else if(j==m-1){
                    if(e[i][j-1]<e[i][j]&&e[i-1][j]<e[i][j]&&e[i+1][j]<e[i][j]){
                        num++;
                    }
                }
                else{
                    if(e[i][j+1]<e[i][j]&&e[i-1][j]<e[i][j]&&e[i][j-1]<e[i][j]&&e[i+1][j]<e[i][j]){
                        num++;
                    }
                }
            }
        }
            else{
                if(n==1&&m!=1){
                    if(e[i][j+1]<e[i][j]&&e[i-1][j]<e[i][j]){
                        num++;
                    }
                   
                }
                else if(m==1&&n!=1){
                    if(e[i-1][j]<e[i][j]&&e[i+1][j]<e[i][j])
                        num++;
                }
            }
        }
    }
    cout<<num;
}