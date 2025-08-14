#include<bits/stdc++.h>
using namespace std;
const int M=1<<9; 
long long g[M],h[M],f[10][M][82],n,k,tot=0;
int main(){
    cin>>n>>k;
    memset(f,0,sizeof(f));
    for(int x=0;x<(1<<n);x++){
        if(!(x&(x>>1))&&!(x&(x<<1)))g[x]=1;
        int w=x;
        while(w){
            if(w%2)h[x]++;
            w/=2;
        }
        if(g[x])f[1][x][h[x]]=1;
    }
    for(int x=2;x<=n;x++){
        for(int y=0;y<(1<<n);y++){
            if(g[y]){
                for(int z=0;z<(1<<n);z++){
                    if(g[z]&&!(y&z)&&!(y&(z>>1))&&!(y&(z<<1))){
                        for(int w=0;w+h[z]<=k;w++)f[x][z][w+h[z]]+=f[x-1][y][w];//w枚举总共放的国王的个数
                    }
                }
            }
        }
    }
    for(int y=0;y<(1<<n);y++)tot+=f[n][y][k];
    cout<<tot;
    return 0;
}