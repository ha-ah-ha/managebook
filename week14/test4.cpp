#include<bits/stdc++.h>
#include<array>
using namespace std;
const int mod=998244353;//模
typedef long long ll;
using matrix=array<array<ll,4>,4>;//定义4*4矩阵类型

matrix multiply(const matrix& a,const matrix& b){//矩阵乘法
    matrix res={};//初始化结果矩阵
    for(int i=0;i<4;i++){
        for(int k=0;k<4;k++){
            if(a[i][k]==0) continue;
            for(int j=0;j<4;j++){
                res[i][j]+=a[i][k]*b[k][j];//矩阵乘法
                res[i][j]%=mod;//取模防止溢出
            }
        }
    }
    return res;
}

matrix power(matrix a,ll n){//快速幂
    matrix res={{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};//单位矩阵
    while(n>0){
        if(n%2==1){
            res=multiply(res,a);//奇数时乘入结果
        }
        a=multiply(a,a);//矩阵平方
        n/=2;
    }
    return res;
}

int main(){
    int t;
    cin>>t;
    matrix m={{{1,1,1,0},{1,1,0,1},{1,0,1,1},{0,1,1,1}}};//状态转移矩阵
    while (t--) {
        ll n;
        cin >> n;
        matrix mat = power(m, n);//计算转移矩阵的n次幂
        cout << mat[0][0] % mod << endl;//输出结果矩阵的左上角元素
    }
}