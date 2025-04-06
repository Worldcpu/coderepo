#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
const int MN=6500;
int T,n,m,tot,dfn[MN],low[MN],ecc,color[MN],s[MN],top,in[MN];
vector<int> adj[MN],sdt[MN];
bool vis[MN];
void tarjan(int u){
    low[u]=dfn[u]=++tot;
    s[++top]=u;
    vis[u]=1;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        ecc++;
        int p;
        do
        {
            p=s[top--];
            vis[p]=0;
            color[p]=ecc;
        } while (p!=u);
    }
}
void bfs(){
    // int maxx=-1e9;
    queue<int> q;
    for(int i=1;i<=ecc;i++){
        if(!in[i]){
            q.push(i);
        }
    }
    if(q.size()>1){
            cout<<"No\n";
            return;
    }
    while (!q.empty())
    {
        int f=q.front();
        q.pop();
        for(int i=0;i<sdt[f].size();i++){
            int v=sdt[f][i];
            in[v]--;
            if(!in[v]){
                q.push(v);
            }
        }
        if(q.size()>1){
            cout<<"No\n";
            return;
        }
    }
    cout<<"Yes\n";
}
int main(){
    cin>>T;
    while (T--)
    {
        tot=ecc=top=0;
        memset(vis,0,sizeof(vis));
         memset(dfn,0,sizeof(dfn));
         memset(low,0,sizeof(low));
         memset(color,0,sizeof(color));
        // memset(dp,0,sizeof(dp));
        memset(in,0,sizeof(in));
        cin>>n>>m;
        for(int i=1;i<MN;i++){
            adj[i].clear();
            sdt[i].clear();
        }
        for(int i=1;i<=m;i++){
            int u,v;
            cin>>u>>v;
            adj[u].push_back(v);
        }
        for(int i=1;i<=n;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        //cout<<"ECC "<<ecc<<endl;
        for(int i=1;i<=n;i++){
            for(int j=0;j<adj[i].size();j++){
                if(color[adj[i][j]]!=color[i]){
                    sdt[color[i]].push_back(color[adj[i][j]]);
                    in[color[adj[i][j]]]++;
                }
            }
        }
        bfs();
    }
    
    return 0;
}