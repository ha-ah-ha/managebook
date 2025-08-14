#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int maxn=1e5;
const int maxprime=100;

void getprime(int c,vector<int>& primes,vector<int>& exps){
    if(c==1){return;}
    for(int i=2;i*i<=c;i++){
        if(c%i==0){
            primes.push_back(i);
            int cnt=0;
            while(c%i==0){
                c=c/i;
                cnt++;
            }
            exps.push_back(cnt);
        }
    }
    if(c>1){
        primes.push_back(c);
        exps.push_back(1);
    }
}

int modpow(long long a, long long b) {
    long long result = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return result;
}

int main(){
    int n,m;
    cin>>n>>m;

   unordered_map<int,vector<long long>> a;
    for(int i=0;i<m;i++){
        int l,r,c;
        long long b;
        cin>>l>>r>>c>>b;
        if(c==1){
            continue;
        }
        vector<int> primes,exps;
        getprime(c,primes,exps);
        for(int j=0;j<primes.size();j++){
            int z=primes[j];
            long long sumexp=(long long)exps[j]*b;
            if(a.find(z)==a.end()){
                a[z]=vector<long long>(n+2,0);
            }
            a[z][l]+=sumexp;
            if(r+1<=n){
                a[z][r+1]-=sumexp;
            }
        }
    }
    long long gcd=1;
    for(auto& p:a){
        int prime=p.first;
        vector<long long>& d=p.second;
        long long cur=0;
        long long minexp=LLONG_MAX;
        for(int i=1;i<=n;i++){
            cur+=d[i];
            minexp=min(minexp,cur);
        }
        if(minexp>0){
            gcd=(gcd*modpow(prime,minexp))%mod;
        }
    }
    cout<<gcd<<endl;
    return 0;
}