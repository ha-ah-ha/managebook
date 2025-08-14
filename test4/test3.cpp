#include<bits/stdc++.h>
#include<array>
using namespace std;
typedef long long ll;

int lowbit(int x){
    return x&-x;
}

void update(vector<ll>& tree,int pos,ll val,int m){
    while(pos<=m){
        tree[pos]+=val;
        pos+=lowbit(pos);
    }
}

ll query(vector<ll>& tree,int pos){
    ll res=0;
    while(pos){
        res+=tree[pos];
        pos-=lowbit(pos);
    }
    return res;
}

int main(){
    ll n,m;
    cin>>n>>m;
    vector<array<ll,3>> ops;
    vector<ll> v;
    for(int i=0;i<m;i++){
        ll q,l,r;
        cin>>q>>l>>r;
        ops.push_back({q,l,r});
        v.push_back(l);
        v.push_back(r);
        if(q==2){
            v.push_back(r+1);
        }
    }
    sort(v.begin(),v.end());
    auto last=unique(v.begin(),v.end());
    v.erase(last,v.end());
    int M=v.size();

    auto get_id = [&](ll x) -> int {
        auto it = lower_bound(v.begin(), v.end(), x);
        return it - v.begin() + 1;
    };

    vector<ll> tree1(M+10,0);
    vector<ll> tree2(M+10,0);

    for(int i=0;i<m;i++){
        ll q=ops[i][0],l=ops[i][1],r=ops[i][2];
        if(q==1){
            int idl=get_id(l);
            int idr=get_id(r);
            update(tree1,idr,1,M);
            update(tree2,idl,1,M);
        }
        else if(q==2){
             int id_l = get_id(l);
            int id_r_plus = get_id(r + 1);
            ll A = query(tree2, id_r_plus - 1);
            ll B = query(tree1, id_l - 1);
            cout<<A-B<<"\n";
        }
    }
    return 0;
}