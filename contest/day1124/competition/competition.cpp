#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=1e9+7; 
int ans,n,m;

struct KDLTree{
    int l,r;
    int val;

    bool operator<(const KDLTree &x)const{
        return l<x.l;
    }
};
set<KDLTree> odt;

auto split(int pos){
    if(pos>m) return odt.end();
    auto it=odt.lower_bound({pos});
    if(it!=odt.end()&&it->l==pos) return it;
    it=prev(it);
    int l=it->l, r=it->r, val=it->val;
    odt.erase(it);
    odt.insert({l,pos-1,val});
    return odt.insert({pos,r,val}).first;
}

void merge(int l,int r,int k){
    auto itr=split(r+1);
    auto itl=split(l);
    for(auto it=itl; it!=itr; ++it){
        int ll = it->l, rr = it->r, val = it->val;
        ans = (ans + ((rr-ll+1)%MOD * ((k-val-1+MOD)%MOD) %MOD * ((n-k+1)%MOD) %MOD) %MOD) %MOD;
        ans = (ans + ((rr-ll+1)%MOD * ((n-k+1)%MOD) %MOD)) %MOD;
    }
    odt.erase(itl,itr);
    odt.insert({l,r,k});
}

int ksm(int a,int b){
    a%=MOD;
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>m;
    odt.insert({1,m,0});
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        merge(l,r,i);
    }
    cout<<ksm(n*(n+1)/2,MOD-2)*ans%MOD<<'\n';

    return 0;
}
