#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15,MOD=1e9+7;
int n,K,ans,pw[MN],inv[MN],siz[MN],invc;
vector<int> adj[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void dfs(int u,int pre){
    siz[u]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        ans=(ans+getC(siz[v],K/2)*getC(n-siz[v],K/2)%MOD)%MOD;
    }
}

signed main(){
    init();
    cin>>n>>K;
    invc=ksm(getC(n,K),MOD-2);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if(K&1){
        cout<<1;
        return 0;
    }
    dfs(1,0);
    cout<<ans*invc%MOD+1;
    return 0;
}
