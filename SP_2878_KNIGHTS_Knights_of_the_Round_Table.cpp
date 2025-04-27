#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e4+15;
int n,m,tot,top,dcc,rt,dfn[MN],low[MN],s[MN],c[MN],bdcc[MN];
vector<int> adj[MN],vdcc[MN];
bool hate[MN][MN],vis[MN];
vector<pir> input;

void tarjan(int u){
    low[u]=dfn[u]=++tot;
    s[++top]=u;
    if(adj[u].empty()&&u==rt){
        vdcc[++dcc].push_back(u);
        bdcc[u]=dcc;
        return;
    }
    for(auto v:adj[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                dcc++;
                int p;
                vdcc[dcc].clear();
                do
                {
                    p=s[top--];
                    bdcc[p]=dcc;
                    vdcc[dcc].push_back(p);
                } while (p!=v);
                vdcc[dcc].push_back(u);
            }
        }else low[u]=min(low[u],dfn[v]);
    }
}

bool color(int u,int id){
    for(auto v:adj[u]){
        if(bdcc[v]!=id) continue;
        if(c[v]==c[u]) return 0;
        if(!c[v]){
            c[v]=3-c[u];
            return color(v,id);
        }
    }
    return 1;
}

void solve(){
    tot=0,dcc=0,top=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            hate[i][j]=0;
        }
        c[i]=0;
        low[i]=dfn[i]=0;
        bdcc[i]=0;
        vis[i]=0;
        vdcc[i].clear();
        adj[i].clear();
        vis[i]=0;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        input.push_back(pir(u,v));
        hate[u][v]=hate[v][u]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(!hate[i][j]){
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            rt=i;
            tarjan(i);
        }
    }
    for(int i=1;i<=dcc;i++){
        for(auto p:vdcc[i]) bdcc[p]=i;
        c[vdcc[i][0]]=1;
        if(!color(vdcc[i][0],i)){
            for(auto p:vdcc[i]) vis[p]=1;
        }
        for(auto p:vdcc[i]) c[p]=0;
    }
    int ans=n;
    for(int i=1;i<=n;i++) if(vis[i]) ans--;
    cout<<ans<<'\n';
}

int main(){
    while(1){
        input.clear();
        cin>>n>>m;
        input.push_back(pir(n,m));
        if(!n&&!m) break;
        solve();
    }
    return 0;
}