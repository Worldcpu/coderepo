#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=155;
ll n,m,MOD,gd,fm=1,ans,tot;
ll jc[MN],inv[MN],jcinv[MN],a[MN];

void init(){
    inv[1]=jc[0]=jcinv[0]=1;
    for(int i=2;i<MN;i++){
        inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
    }
    for(int i=1;i<=n;i++){
        jc[i]=jc[i-1]*i%MOD;
    }
    for(int i=1;i<=n;i++){
        jcinv[i]=jcinv[i-1]*inv[i]%MOD;
    }
}

ll ksm(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1){
            ret=(ret*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ret;
}

void dfs(ll lft,ll bef,ll cnt){
    if(!lft){
        ans=(ans+ksm(m,gd)*fm)%MOD;
        return;
    }
    int tmpgd=gd,tmpfm=fm;
    for(ll i=1;i<=bef;i++){
        a[++tot]=i;
        gd=tmpgd+i/2;
        for(int j=1;j<tot;j++){
            gd+=__gcd(a[j],i);
        }
        fm=tmpfm*inv[i]%MOD;
        if(i==a[tot-1]){
            fm=fm*inv[cnt+1]%MOD;
            dfs(lft-i,min(lft-i,i),cnt+1);
        }else dfs(lft-i,min(lft-i,i),1);
        tot--;
    }
}

int main(){

    cin>>n>>m>>MOD;
    init();
    dfs(n,n,0);
    cout<<ans;
    return 0;
}