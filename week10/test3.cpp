#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class tree{
private:
    vector<ll> tree1;
public:
    tree(int size){
        tree1.resize(size+1,0);
    }
    void update(int idx,ll delta){
        while(idx<tree1.size()){
            tree1[idx]+=delta;
            idx+=idx&-idx;
        }
    }
    ll sum(int idx){
        ll result=0;
        while(idx>0){
            result+=tree1[idx];
            idx-=idx&-idx;
        }
        return result;
    }
};

int main(){
    int n,q;
    cin>>n>>q;
    tree tree1(n);
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        tree1.update(i,a[i]);
    }
    while(q--){
        int order,b,c;
        cin>>order>>b>>c;
        if(order==1){
            tree1.update(b,c);
        }
        if(order==2){
            ll sum1=tree1.sum(c);
            ll sum2=tree1.sum(b-1);
            cout<<(sum1-sum2)<<"\n";
        }
    }
    return 0;
}