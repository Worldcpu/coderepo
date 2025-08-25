#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7;
int f[MN][2],a[MN],rt,n,tot;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void dfs(int &u,int l,int r,int val){
    u=++tot;
    f[u][0]=1;
    if(l>r) return;
    int minn=1e9,ttot=0;
    vector<int> p(r-l+11);
    for(int i=l;i<=r;i++) minn=min(minn,a[i]);
    p[++ttot]=l-1;
    for(int i=l;i<=r;i++) if(minn==a[i]) p[++ttot]=i;
    p[++ttot]=r+1;
    f[u][1]=1;
    for(int i=2;i<=ttot;i++){
        int nxt=0;
        dfs(nxt,p[i-1]+1,p[i]-1,minn);
        f[u][0]=f[u][0]*f[nxt][0]%MOD;
        f[u][1]=f[u][1]*(f[nxt][0]+f[nxt][1])%MOD;
    }
    int sum1=ksm(2,ttot-2),sum2=ksm(2,minn-val);
    int f0=f[u][0]; 
    f[u][1]=(sum1*f[u][1]%MOD+((sum2-2+MOD)%MOD)*f0%MOD)%MOD;
    f[u][0]=sum2*f0%MOD;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    dfs(rt,1,n,0);
    cout<<(f[rt][1]+MOD)%MOD<<"\n";
    return 0;
}
