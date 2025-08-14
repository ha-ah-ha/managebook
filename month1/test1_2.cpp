#include<bits/stdc++.h>
using namespace std;

struct acard{
    int a;//大小
    int b;//花色
    acard(int a1=0,int b1=0){
        a=a1;
        b=b1;
    }
};

int num[9]={0};



bool fun2(acard c1,acard c2,acard c3,acard c4,acard c5){
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
    if (hand[1]!=hand[2]||hand[3]!=hand[2]||hand[3]!=hand[4])
        return false;
    else
        return true;
}

bool fun3(acard c1,acard c2,acard c3,acard c4,acard c5){
    vector<int> hand;
    hand.push_back(c1.a);
    hand.push_back(c2.a);
    hand.push_back(c3.a);
    hand.push_back(c4.a);
    hand.push_back(c5.a);
    sort(hand.begin(), hand.end());
}

int main(){
    int a,b;
    cin>>a>>b;
    int a1,b1,a2,b2;
    cin>>a1>>b1>>a2>>b2;
    acard card1(a1,b1),card(a2,b2);
    vector<acard> cards;
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            if(!((i==a1&&i==b1)||(i==a2&&j==b2))){
                cards.push_back(acard(i,j));
            }
        }
    }

    for(int i=0;i<a*b-4;i++){
        for(int j=i+1;j<b*a-3;j++){
            for(int k=j+1;j<b*a-2;k++){
                if()
            }
        }
    }
}