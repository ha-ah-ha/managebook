#include<bits/stdc++.h>
using namespace std;

struct point{
    int r,g,b;
    point(int a,int b,int c):r(a),g(b),b(c){}
};

int main(){
    int h,w;
    cin>>h>>w;
    vector<vector<point>> pic(h);
    //vector<vector<point>> newpic(h);
    int num1=0;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            int r,g,b;
            cin>>r>>g>>b;
            point ap(r,g,b);
            pic[i].push_back(ap);
            num1++;
        }
    }
    int num2=0;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            int r,g,b;
            cin>>r>>g>>b;
            point ap(r,g,b);
            if(ap.b!=pic[i][j].b||ap.g!=pic[i][j].g||ap.r!=pic[i][j].r){
                num2++;
            }
        }
    }
    int size1=(h*w-num2*2)*24;
    cout<<size1;
}