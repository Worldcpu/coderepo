#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
struct Edge
{
    int v,w;
};
int n,m,tot,dcc,top,s[MN],color[MN],in[MN],low[MN],dfn[MN],f[MN];
vector<Edge> adj[MN],adj2[MN];
vector<int> vdcc[MN];
bool vis[MN];

void tarjan(int u){
    low[u]=dfn[u]=++tot;
    s[++top]=u;
    vis[u]=1;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        dcc++;
        int p;
        do
        {
            p=s[top--];
            color[p]=dcc;
            vdcc[dcc].push_back(p);
            vis[p]=0;
        } while (p!=u);
        
    }
}

void toposort(){
    queue<int> q;
    for(int i=1;i<=dcc;i++){
        if(!in[i]){
            q.push(i);
            f[i]=1;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto e:adj2[u]){
            in[e.v]--;
            f[e.v]=max(f[e.v],f[u]+e.w);
            if(!in[e.v]) q.push(e.v);
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int mode,u,v;
        cin>>mode>>u>>v;
        if(mode==1){
            adj[v].push_back({u,0});
            adj[u].push_back({v,0});
            //cout<<u<<" "<<v<<" 0\n"<<v<<" "<<u<<" 0\n";
        }
        if(mode==2){
            adj[u].push_back({v,1});
            //cout<<u<<" "<<v<<" 1\n";
        }
        if(mode==3){
            adj[v].push_back({u,0});
            // cout<<u<<" "<<v<<" 0\n";
        }
        if(mode==4){
            adj[v].push_back({u,1});
            // cout<<v<<" "<<u<<" 1\n";
        }
        if(mode==5){
            adj[u].push_back({v,0});
            // cout<<u<<" "<<v<<" 0\n";
        }
    }
    //for(int i=1;i<=n;i++) adj[0].push_back({i,1});
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=n;i++){
        for(auto e:adj[i]){
            if(color[i]!=color[e.v]){
                adj2[color[i]].push_back({color[e.v],e.w});
                in[color[e.v]]++;
            }
            if(color[i]==color[e.v]&&e.w==1){
                cout<<-1;
                return 0;
            }
        }
    }
    toposort();
    int ans=0;
    for(int i=1;i<=dcc;i++){
        ans+=f[i]*vdcc[i].size();
    }
    cout<<ans;
    return 0;
}