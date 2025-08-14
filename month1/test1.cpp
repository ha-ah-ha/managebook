#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

// struct card{
//     int num;
//     int color;
//     card(int n,int c):num(n),color(c){}
// };
int n1,c1,n2,c2;
int a;//数字
int b;//花色
int numbers[5];
void fun1(){
    if(abs(n1-n2)>4||c2!=c1||b<5||a<5){
        numbers[0]=0;
        return;
    }
    int n=0;
    int min1=min(n1,n2),max1=max(n1,n2);
    int max2=min1+4,min2=min1;
    while(min2>=0&&max1<=max2){
        if(max2<=a){
            n++;
        }
        min2--;
        max2--;
    }
    numbers[0]=n;

}

void fun2(){
    if(b<4){
        numbers[1]=0;
        return;
    }
    if(n1==n2){
        int n=0;
        for(int i=0;i<b;i++){
            if(i!=c1&&i!=c2){
                for(int j=i+1;j<b;j++){
                    if(j!=c1&&j!=c2){
                        for(int k=0;k<a;k++){
                            n++;
                        }
                    }
                }
            }
        }
        numbers[1]=n;
        return;
    }
    if(n1!=n2){
        int n=0;
        for(int i=0;i<b;i++){
            if(i!=c1){
                for(int j=i+1;j<b;j++){
                    if(j!=c1){
                        for(int k=j+1;k<b;k++){
                            if(k!=c1){
                                n++;
                            }
                        }
                    }
                }
            }
        }
        numbers[1]=n*2;
        return;
    }
}

void fun3(){
    if(b<3){
        numbers[2]=0;
        return;
    }
    if(n1!=n2){//两张牌颜色不同
        int n=0;
        for(int k=0;k<b;k++){
            if(k!=c2){
                for(int i=0;i<b;i++){
                    if(i!=c1){
                        for(int j=i+1;j<b;j++){
                            if(j!=c1){
                                n++;
                            }
                        }
                    }
                }
            }
        }
        numbers[2]=n*2;
    }
    if(n1==n2){//两张牌颜色相同
        int n=0;
        for(int i=0;i<b;i++){//已经抽到的两张牌作为3张
            if(i!=c1&&i!=c2){
                for(int j=0;j<a;j++){
                    if(j!=n1){
                        for(int k=0;k<b;k++){
                            for(int m=k+1;m<b;m++){
                                n++;
                            }
                        }
                    }
                }
            }
        }
        for(int i=0;i<a;i++){//作为两张相同的的
            if(i!=n1){
                for(int j=0;j<b;j++){
                    for(int k=j+1;k<b;j++){
                        for(int m=k+1;m<b;m++){
                            n++;
                        }
                    }
                }
            }
        }
        numbers[2]=n*2;
    }
}

void fun4(){
    if(b<5||c1!=c2){
        numbers[3]=0;
        return;
    }
    int n;

}

int main(){
    cin>>a>>b;
    int** cards=new int*[a];
    for(int i=0;i<b;i++){
        cards[i]=new int[b];
    }
    cin>>n1>>c1>>n2>>c2;

}