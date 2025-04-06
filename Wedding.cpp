#include<bits/stdc++.h>
using namespace std;
const int MN=1e6+15;
int n,m,tot,vdcc,color[2*MN],dfn[2*MN],low[2*MN],s[2*MN],top;
bool vis[2*MN];
vector<int> adj[2*MN];
void tarjan(int u){
    low[u]=dfn[u]=++tot;
    s[++top]=u;
    vis[u]=1;
    for(auto v:adj[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        vdcc++;
        int p;
        do
        {
            p=s[top--];
            vis[p]=0;
            color[p]=vdcc;
        } while (p!=u);
    }
}
void clean(){
    top=tot=vdcc=0;
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(color,0,sizeof(color));
    for(int i=1;i<=4*n;i++){
        // vis[i]=dfn[i]=low[i]=color[i]=0;
        adj[i].clear();
    }
}
void solve(){
    clean();
    for(int i=1;i<=m;i++){
        int u,v;
        char uc,vc;
        cin>>u>>uc>>v>>vc;
        u++;
        v++;
        if(uc=='w'&&vc=='h'){
            adj[v+n].push_back(u+n);
            adj[u].push_back(v);
        }else if(uc=='h'&&vc=='w'){
            adj[u+n].push_back(v+n);
            adj[v].push_back(u);
        }else if(uc=='w'&&vc=='w'){
            adj[u].push_back(v+n);
            adj[v].push_back(u+n);
        }else if(uc=='h'&&vc=='h'){
            adj[v+n].push_back(u);
            adj[u+n].push_back(v);
        }
    }
    adj[1].push_back(n+1);
    for(int i=1;i<=2*n;i++){
        if(!dfn[i]) tarjan(i);
    }
    for(int i=1;i<=n;i++){
        if(color[i]==color[i+n]){
            cout<<"bad luck\n";
            return;
        }
    }
    for(int i=2;i<=n;i++){
        if(color[i]>color[i+n]){
            cout<<i-1<<"w ";
        }else cout<<i-1<<"h ";
    }
    cout<<"\n";
}
int main(){
    while (1)
    {
        cin>>n>>m;
        if(!n&&!m){
            break;
        }
        solve();
    }
    
    return 0;
}