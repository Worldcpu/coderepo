#include<bits/stdc++.h>
#define int long long
#define pir pair<int,char>
using namespace std;
constexpr int MN=1e6+15;
struct Edge{
    int v;
    char w;
};
int n,m,q,ftot,ans,f[MN][2];
int cnt[MN][3],fcol[MN];
vector<Edge> adj[MN];
vector<pir> col[MN];
vector<int> G[MN];

namespace YFTarjan{
    int dfn[MN],low[MN],stk[MN],tp,dtot;

    void init(){
        ftot=n;
    }

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        stk[++tp]=u;
        for(auto e:adj[u]){
            int v=e.v;
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]){
                    ftot++;
                    int x;
                    do{
                        x=stk[tp--];
                        G[ftot].push_back(x);
                        G[x].push_back(ftot);
                    }while(x!=v);
                    G[ftot].push_back(u);
                    G[u].push_back(ftot);
                }
            }else low[u]=min(low[u],dfn[v]);
        }
    }
}

namespace Tree{
    int fa[MN];

    void dfs(int u,int pre){
        fa[u]=pre;
        for(auto v:G[u]){
            if(v==pre) continue;
            dfs(v,u);
        }
    }

    void dodp(int u,int pre){
        if(u<=n) f[u][0]++,f[u][1]++;
        else{
            if(fcol[u]==0) f[u][1]=0;
            else if(fcol[u]==1) f[u][0]=0;
            else f[u][0]=f[u][1]=0;
        }
        for(auto v:G[u]){
            if(v==pre) continue;
            dodp(v,u);
            if(u<=n){
                ans-=f[u][0]*f[v][0];
                ans-=f[u][1]*f[v][1];
                f[u][0]+=f[v][0];
                f[u][1]+=f[v][1];
            }else{
                if(fcol[u]==0){
                    ans-=f[u][0]*f[v][0];
                    f[u][0]+=f[v][0];
                }
                else if(fcol[u]==1){
                    ans-=f[u][1]*f[v][1];
                    f[u][1]+=f[v][1];
                }
            }
        }
    }

}using namespace Tree;

void init(){
    for(int i=1;i<=n;i++){
        for(auto e:adj[i]){
            int v=e.v,fd;
            if(v<=i) continue;
            if(fa[i]==fa[v]) fd=fa[i];
            else if(fa[fa[i]]==v) fd=fa[i];
            else fd=fa[v];
            col[fd].push_back(pir(i,e.w));
            col[fd].push_back(pir(v,e.w));
        }
    }
    for(int i=n+1;i<=ftot;i++){
        int cnt1=0,cnt2=0,cnt3=0;
        for(auto now:col[i]){
            if(now.second=='d') cnt[now.first][0]++;
            else cnt[now.first][1]++;
        }
        for(auto v:G[i]){
            if(cnt[v][0]*cnt[v][1]>0) cnt3++;
            else if(cnt[v][0]) cnt1++;
            else cnt2++;
        }
        for(auto now:col[i]){
            if(now.second=='d') cnt[now.first][0]--;
            else cnt[now.first][1]--;
        }
        if(cnt3>2) fcol[i]=3;
        else if(cnt3==2) fcol[i]=2,ans--;
        else if(cnt1>0) fcol[i]=0;
        else fcol[i]=1;
    }
}

signed main(){
    int qwq;
    cin>>qwq>>n>>m;
    ans=n*(n-1)/2;
    for(int i=1;i<=m;i++){
        int u,v;
        char c;
        cin>>u>>v>>c;
        adj[u].push_back({v,c});
        adj[v].push_back({u,c});
    }
    YFTarjan::init();
    YFTarjan::tarjan(1);
    dfs(1,0);
    init();
    dodp(1,0);
    cout<<ans;

    return 0;
}