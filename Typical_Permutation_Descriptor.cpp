#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,a[MN],pw[MN],inv[MN];
vector<int> vct[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int solve(int l,int r){
    if(l>r) return 1;
    int it=*(--upper_bound(vct[l-1].begin(),vct[l-1].end(),r));
    if(it==l){
        return solve(l+1,r);
    }
    if(it==r) return solve(l,r-1);
    return solve(l,it-1)*solve(it+1,r)%MOD*getC(r-l,it-l)%MOD;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        vct[a[i]].push_back(i);
    }
    cout<<solve(1,n);
    return 0;
}