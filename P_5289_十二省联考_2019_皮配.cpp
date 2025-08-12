#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2520,MOD=998244353;
int F[MN][MN],G[MN][MN],f[MN],g[MN],h[MN],s[MN],b[MN],sumb[MN],sums,n,c,c0,c1,d0,d1,C,K,D,ans;
bool hc[MN];

void init(){
    memset(F,0,sizeof(F));
    memset(G,0,sizeof(G));
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    ans=C=D=0; sums=0;
    for(int i=1;i<=n;i++){
        h[i]=-1;
        sumb[i]=0;
        hc[i]=false;
    }
}

void solve(){
    cin>>n>>c>>c0>>c1>>d0>>d1;
    init();
    for(int i=1;i<=n;i++){
        cin>>b[i]>>s[i];
        sums+=s[i];
        sumb[b[i]]+=s[i];
    }
    cin>>K;
    for(int i=1;i<=K;i++){
        int x;cin>>x>>h[x];
        hc[b[x]]=true;
    }
    f[0]=1;
    for(int i=1;i<=c;i++) if(!hc[i]&&sumb[i]){
        for(int j=c0;j>=sumb[i];j--) f[j]=(f[j]+f[j-sumb[i]])%MOD;
    }
    for(int i=1;i<=c0;i++) f[i]=(f[i-1]+f[i])%MOD;
    g[0]=1;
    for(int i=1;i<=n;i++) if(h[i]==-1){
        for(int j=d0;j>=s[i];j--) g[j]=(g[j]+g[j-s[i]])%MOD;
    }
    for(int i=1;i<=d0;i++) g[i]=(g[i-1]+g[i])%MOD;
    F[0][0]=1;
    for(int ct=1;ct<=c;ct++) if(hc[ct]){
        C+=sumb[ct]; C=min(C,c0);
        for(int i=0;i<=C;i++) for(int j=0;j<=D;j++) G[i][j]=F[i][j];
        for(int x=1;x<=n;x++) if(h[x]!=-1&&b[x]==ct){
            int t=s[x]; D+=t; D=min(D,d0);
            if(h[x]==1){ 
                for(int i=0;i<=C;i++){for(int j=D;j>=t;j--) F[i][j]=F[i][j-t]; for(int j=0;j<t;j++) F[i][j]=0;}
            }
            if(h[x]>=2){ 
                for(int i=0;i<=C;i++) for(int j=D;j>=t;j--) F[i][j]=(F[i][j]+F[i][j-t])%MOD;
            }
            if(h[x]==3){ 
                for(int i=0;i<=C;i++){for(int j=D;j>=t;j--) G[i][j]=G[i][j-t]; for(int j=0;j<t;j++) G[i][j]=0;}
            }
            if(h[x]<=1){ 
                for(int i=0;i<=C;i++) for(int j=D;j>=t;j--) G[i][j]=(G[i][j]+G[i][j-t])%MOD;
            }
        }
        int t=sumb[ct];
        if(t>0){
            for(int i=C;i>=t;i--) for(int j=0;j<=D;j++) F[i][j]=F[i-t][j];
            for(int i=0;i<t;i++) for(int j=0;j<=D;j++) F[i][j]=0;
        }
        for(int i=0;i<=C;i++) for(int j=0;j<=D;j++) F[i][j]=(F[i][j]+G[i][j])%MOD;
    }
    for(int i=0;i<=C;i++) for(int j=0;j<=D;j++){
        int l1=max(0ll,sums-c1-i),r1=c0-i; if(l1>r1) continue;
        int l2=max(0ll,sums-d1-j),r2=d0-j; if(l2>r2) continue;
        int ret1=f[r1],ret2=g[r2];
        if(l1) ret1=(ret1-f[l1-1]+MOD)%MOD;
        if(l2) ret2=(ret2-g[l2-1]+MOD)%MOD;
        ans=(ans+ret1*ret2%MOD*F[i][j])%MOD;
    }
    cout<<(ans+MOD)%MOD<<'\n';
}

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T;cin>>T;while(T--) solve();
    return 0;
}
