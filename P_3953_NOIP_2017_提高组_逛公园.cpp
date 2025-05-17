#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
struct Edge{
    int v,w;
};
int n,m,K,P,d,f[MN][60];
bool vis[MN][60];
vector<Edge> adj[MN],fadj[MN],g[MN];
vector<int> adj0[MN];

struct Tarjan{
    int tot,top,vdcc,s[MN],dfn[MN],low[MN],col[MN],colw[MN];
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++tot;
        s[++top]=u;
        vis[u]=1;
        for(auto v:adj0[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]) low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u]){
            int p;
            vdcc++;
            do{
                p=s[top--];
                vis[p]=0;
                col[p]=vdcc;
                colw[vdcc]++;
            }while(p!=u);
        }

    }

    void getc(){
        vdcc=tot=top=0;
        for(int i=1;i<=n;i++){
            if(!dfn[i]) tarjan(i);
        }
    }
}tj;

struct Dijk{
#define pir pair<int,int>
    priority_queue<pir,vector<pir>,greater<pir>> q;
    int dis1[MN],dis2[MN];
    bool vis1[MN],vis2[MN];

    void dijk1(int st){
        memset(dis1,0x3f,sizeof(dis1));
        dis1[st]=0;
        q.push(pir(0,st));
        while(!q.empty()){
            auto fr=q.top();
            q.pop();
            int u=fr.second;
            if(vis1[u]) continue;
            vis1[u]=1;
            for(auto e:adj[u]){
                if(dis1[e.v]>dis1[u]+e.w){
                    dis1[e.v]=dis1[u]+e.w;
                    if(!vis1[e.v]) q.push({dis1[e.v],e.v});
                }
            }
        }
    }

    void dijk2(int st){
        memset(dis2,0x3f,sizeof(dis2));
        dis2[st]=0;
        q.push(pir(0,st));
        while(!q.empty()){
            auto fr=q.top();
            q.pop();
            int u=fr.second;
            if(vis2[u]) continue;
            vis2[u]=1;
            for(auto e:fadj[u]){
                if(dis2[e.v]>dis2[u]+e.w){
                    dis2[e.v]=dis2[u]+e.w;
                    if(!vis2[e.v]) q.push({dis2[e.v],e.v});
                }
            }
        }
    }

#undef pair
}dj;

int dfs(int u,int k){
    if(vis[u][k]) return f[u][k];
    vis[u][k]=1;
    for(auto e:g[u]){
        int kk=dj.dis1[u]+k-dj.dis1[e.v]-e.w;
        if(kk>=0&&kk<=K){
            f[u][k]+=dfs(e.v,kk);
            f[u][k]%=P;
        }
    }
    return f[u][k];
}

void init(){
    for(int i=1;i<=n;i++){
        tj.vis[i]=dj.vis1[i]=dj.vis2[i]=0;
        tj.dfn[i]=tj.low[i]=tj.col[i]=0;
        adj[i].clear();
        fadj[i].clear();
        g[i].clear();
        adj0[i].clear();
        for(int k=0;k<=K;k++){
            vis[i][k]=f[i][k]=0;
        }
    }
}

void solve(){
    cin>>n>>m>>K>>P;
    init();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(w==0) adj0[u].push_back(v);
        adj[u].push_back({v,w});
        fadj[v].push_back({u,w});
    }
    dj.dijk1(1);
    dj.dijk2(n);
    tj.getc();
    for(int i=1;i<=n;i++){
        for(auto e:adj[i]){
            int v=e.v;
            if(tj.col[i]==tj.col[v]){
                if(dj.dis1[i]<1e9&&dj.dis2[v]<1e9&&dj.dis1[i]+dj.dis2[v]<=dj.dis1[n]+K){
                    cout<<-1<<'\n';
                    return;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(auto e:adj[i]){
            if(tj.col[i]!=tj.col[e.v]){
                g[e.v].push_back({i,e.w});
            }
        }
    }
    f[1][0]=1%P;
    vis[1][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=K;j++){
            f[i][j]=dfs(i,j);
        }
    }
    int ans=0;
    for(int i=0;i<=K;i++) ans=(ans+f[n][i])%P;
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--) solve();
}
