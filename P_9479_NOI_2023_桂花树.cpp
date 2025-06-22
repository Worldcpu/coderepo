#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
constexpr int MN=3e4+15,MK=(1<<11)+15,MOD=1e9+7;
int fa[MN],f[MK],g[MK],n,m,K,c,T;

void solve(){
    memset(f,0,sizeof(f));
    cin>>n>>m>>K;
    int mk=1<<K;
    for(int i=2;i<=n;i++) cin>>fa[i];
    f[0]=1;
    for(int i=0;i<m;i++){
        memset(g,0,sizeof(g));
        for(int s=0;s<1<<K;s++){
            if(!f[s]) continue;
            int tmp=s;
            while(tmp){
                int lwb=tmp&-tmp;
                int nxt=(s^lwb)<<1;
                if(nxt<(1<<K)) (g[nxt]+=f[s])%=MOD;
                tmp^=lwb;
            }
            int nxt=s<<1;
            int c=n+i+__builtin_popcountll(s);
            if(nxt<(1<<K)){
                (g[nxt]+=f[s]*(c*2-1)%MOD)%=MOD;
                (g[nxt|1]+=f[s]*(c-1)%MOD)%=MOD;
            }
        }
        swap(f,g);
    }
    cout<<f[0]<<'\n';
}

signed main(){
    cin>>c>>T;
    while(T--){
        solve();
    }
    return 0;
}
