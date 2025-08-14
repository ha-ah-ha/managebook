
#include<iostream>
#include<vector>
using namespace std;

int n,k;//全局变量，方便函数书写
vector<int> numbers;//存放数字

bool isprime(int number){//检验是否为素数
    for(int i=2;i*i<=number;i++){//遍历小于等于sqrt(x)的所有数
        if(number%i==0){//如果余数为0
            return false;//那么就不是素数
        }
    }
    return true;
}


int result=0;//记录符合要求的个数
int dfs(int begin,int num,int sum){//深度优先搜索，输入从第begin数开始、已经选的数字个数
                                   //以及此时的数的总和
    if(num==k){//已经选了k个数，说明已经出来一种和了
        if(isprime(sum)){//检测是否为素数
            result++;
        }
    }
    for(int i=begin;i<n;i++){//从这个数开始向后遍历数

        dfs(i+1,num+1,sum+numbers[i]);//从这个树后遍历每一个数，进一步深度搜索。
    }
    return result;
}

int main(){
    cin>>n>>k;//输入数的个数以及选数的个数
    for(int i=0;i<n;i++){
        int num1;
        cin>>num1;
        numbers.push_back(num1);//输入每一个数
    }
    cout<<dfs(0,0,0);//输出结果
}