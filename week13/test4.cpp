#include<bits/stdc++.h>
using namespace std;
const int M=1<<10;
long long dp[10][M][82];
int main(){
    int n,k;
    cin>>n>>k;
    long long g[M],h[M];
    memset(dp,0,sizeof dp);
    memset(h,0,sizeof h);
    memset(g,0,sizeof g);
    for(int i=0;i<(1<<n);i++){
        if(!(i&(i>>1))&&!(i&(i<<1))){
            g[i]=1;
        }
        int w=i;
        while(w){
            if(w%2){h[i]++;}
            w/=2;
        }
        if(g[i]){
            dp[1][i][h[i]]=1;
        }
    }
    for(int x=2;x<=n;x++){
        for(int y=0;y<(1<<n);y++){
            if(g[y]){
                for(int z=0;z<(1<<n);z++){
                    if(g[z]&&!(y&z)&&!(y&(z>>1))&&!(y&(z<<1))){
                        for(int w=0;w+h[z]<=k;w++){
                            dp[x][z][w+h[z]]+=dp[x-1][y][w];
                        }
                    }
                }
            }
        }
    }
    long long ans=0;
    for(int y=0;y<(1<<n);y++){
        ans+=dp[n][y][k];
    }
    cout<<ans;
}