#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M=998244353;
int main(){
    int n,m;
    cin>>n>>m;
    int a[101],f[101][10001]={0};
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j==a[i]) f[i][j]=(f[i-1][j]+1)%M;
            if(j>a[i]) f[i][j]=(f[i-1][j]+f[i-1][j-a[i]])%M;
            if(j<a[i]) f[i][j]=(f[i-1][j])%M;
        }
    }
    cout<<f[n][m];
    return 0;
}