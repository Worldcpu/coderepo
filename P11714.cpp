#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=19,MOD=1e9+7;
int n,m,f[1<<MN],g[1<<MN],in[MN],out[MN],e1[1<<MN],e2[1<<MN],pw[1<<MN],pos[1<<MN];

int lowbit(int x){
    return x&-x;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<1<<MN;i++){
        pw[i]=pw[i-1]*2%MOD;
    }
}

int popcount(int x){
    return __builtin_popcountll(x);
}

signed main(){
    initpw();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        out[u]|=(1<<v-1);
        in[v]|=(1<<u-1);
    }
    for(int i=0;i<n;i++){
        pos[1<<i]=i+1;
    }
    for(int s=1;s<(1<<n);s++){
        int x=lowbit(s);
        e2[s]=e2[s-x]+popcount(in[pos[x]]&s)+popcount(out[pos[x]]&s);
    }
    for(int s=1;s<(1<<n);s++){
        e1[s]=0;
        for(int t=(s-1)&s;t;t=(t-1)&s){
            int x=lowbit(s-t);
            e1[t]=e1[t+x]+popcount(in[pos[x]]&t)-popcount(out[pos[x]]&(s-t));
        }
        for(int t=(s-1)&s;t;t=(t-1)&s){
            if(lowbit(s)!=lowbit(t)) continue;
            g[s]=(g[s]-f[t]*g[s-t]%MOD+MOD)%MOD;
        }
        f[s]=pw[e2[s]];
        for(int t=s;t;t=(t-1)&s){
            f[s]=(f[s]-g[t]*pw[e1[t]+e2[s-t]]%MOD+MOD)%MOD;
        }
        g[s]=(g[s]+f[s])%MOD;
    }
    cout<<f[(1<<n)-1];

    return 0;
}