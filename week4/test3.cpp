#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n;//n个商店
        cin>>n;
        int * b=new int[n];//判断在该店是否应该卖出
        int* a=new int[n];//每个商店购买或卖出商品的价格
        for(int j=0;j<n;j++){
            cin>>a[j];//输入每个商品的价格
            b[j]=0;//初始化卖出点
        }
        for(int j=0;j<n-1;j++){
            if(a[j]>a[j+1]){
                b[j]=1;//当后一个的价格比这个价格小的话，那么在这个段里当前价格更高，所以应该卖出
            }
        }
        b[n-1]=1;//最后必须卖出
        int buy=a[0];//买入的价格，第一家店一定会买入
        int num=0;//交易次数
        long long sumvalue=0;//总收益
        for(int j=0;j<n;j++){//遍历所有商店
            if(b[j]==1){//当应该卖出时
                long long h=sumvalue;
                sumvalue+=a[j]-buy;
                if(h!=sumvalue){
                    num+=2;
                }
                if(j==n-1){
                    break;
                }
                else{
                    buy=a[j+1];
                }
            }
        }
        cout<<sumvalue<<' '<<num<<endl;
    }
    return 0;
}