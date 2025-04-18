#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e6+15;
struct Edge{
    int v,w;
};
int n,len,fa[MN],dfn[MN],tot,lp[MN];
ll d[MN];
vector<Edge> adj[MN];
ll q[MN<<1],s[MN<<1],ql,qr,anszj;
bool vis[MN];

void dfs(int u,int pre){
    dfn[u]=++tot;
    fa[u]=pre;
    for(auto e:adj[u]){
        if(e.v==pre) continue;
        if(dfn[e.v]){
            if(dfn[e.v]<dfn[u]) continue;
            lp[++len]=e.v;
            for(;e.v!=u;e.v=fa[e.v]) lp[++len]=fa[e.v];	
        }else dfs(e.v,u);
    }
}

void getzj(int u,int pre){
    vis[u]=1;
    for(auto e:adj[u]){
        if(e.v==pre||vis[e.v]) continue;
        getzj(e.v,u);
        anszj=max(anszj,1ll*d[u]+d[e.v]+e.w);
        d[u]=max(d[u],d[e.v]+e.w);
    }
}

ll solve(int rt){
    ll ans1=0,ans2=0;
    len=tot=0;
    dfs(rt,0);
    lp[0]=lp[len];
    for(int i=1;i<=len;i++){
        vis[lp[i]]=1;
    }
    for(int i=1;i<=len;i++){
        anszj=0;
        getzj(lp[i],0);
        ans1=max(ans1,anszj);
    }
    if(len==2){
        for(auto e:adj[lp[1]]){
            if(e.v==lp[2]) ans2=max(ans2,1ll*d[lp[1]]+d[lp[2]]+e.w);
        }
        return max(ans1,ans2);
    }
    for(int i=1;i<=len;i++){
        for(auto e:adj[lp[i]]){
            if(e.v==lp[i-1]){
                s[i]=s[i-1]+e.w;
            }
        }
    }
    for(int i=1;i<=len;i++){
        s[len+i]=s[len]+s[i];
    }
    ql=1,qr=0;
    q[++qr]=0;
    for(int i=1;i<=len*2;i++){
        while(ql<=qr&&q[ql]<=i-len) ql++;
        ans2=max(ans2,d[lp[q[ql]%len]]+d[lp[i%len]]+s[i]-s[q[ql]]);
        while(ql<=qr&&s[q[qr]]-d[lp[q[qr]%len]]>=s[i]-d[lp[i%len]]) qr--;
        q[++qr]=i;
    }
    return max(ans1,ans2);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int v,w;
        cin>>v>>w;
        adj[i].push_back({v,w});
        adj[v].push_back({i,w});
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(!vis[i]) ans+=solve(i);
    }
    cout<<ans;
    return 0;
}