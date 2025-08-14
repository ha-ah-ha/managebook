#include<bits/stdc++.h>
using namespace std;
vector<int> maxtree;//线段树数组，用于维护区间的最大值
int maxsize;//线段树的最大容量

void update(int node,int l,int r,int p,int val){//更新函数，node代表当前节点索引，节点覆盖区间[l,r]
    //需要更新的位置p，以及新的值val
    if(l==r){//叶子节点，直接更新
        maxtree[node]=val;
        return;
    }
    int mid=(l+r)/2;
    if(p<=mid){
        update(2*node+1,l,mid,p,val);//递归更新左子树
    }
    else{
        update(2*node+2,mid+1,r,p,val);//递归更新右子树
    }
    maxtree[node]=max(maxtree[2*node+1],maxtree[2*node+2]);//合并左右子树结果
}
int query(int node,int l,int r,int ql,int qr){//查询函数。[ql,qr]为准备查询的区间
    if(qr<l||ql>r){return 0;}
    if(ql<=l&&r<=qr){return maxtree[node];}//区间[ql,qr]完全包含[l,r]
    int mid=(l+r)/2;
    int left=query(2*node+1,l,mid,ql,qr);//查询左子树
    int right=query(2*node+2,mid+1,r,ql,qr);//查询右子树
    return max(left,right);//合并左右子树结果
}
int main(){
    int m,p;
    cin>>m>>p;
    maxsize=m;//初始化线段树容量
    maxtree.resize(4*maxsize,0);//初始化线段树
    int n=0,a=0;
    for(int i=0;i<m;i++){
        char op;
        cin>>op;
        if(op=='A'){//添加菜品
            int t;
            cin>>t;
            int val=(a+t)%p;//计算美味度
            update(0,0,maxsize-1,n,val);//更新
            ++n;
        }
        else{//点菜操作
            int l;
            cin>>l;
            int ql=n-l;//区间左
            int qr=n-1;//区间右
            int res=query(0,0,maxsize-1,ql,qr);//查询
            cout<<res<<endl;
            a=res;
        }
    }
    return 0;
}