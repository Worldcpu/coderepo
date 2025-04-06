#include<bits/stdc++.h>
using namespace std;
const int MN=8e4*3;
int n,m,top,s[MN],tot,vdcc,dcc[MN],dfn[MN],low[MN];
vector<int> adj[MN];
bool vis[MN];
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
            dcc[p]=vdcc;
            vis[p]=0;
        } while (p!=u);
        
    }
}
int f(int x){
    return x&1?x+1:x-1;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        int nu=f(u),nv=f(v);
        adj[u].push_back(nv);
        adj[v].push_back(nu);
    }
    for(int i=1;i<=n*2;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=2;i<=2*n;i+=2){
        if(dcc[i]==dcc[f(i)]){
            cout<<"NIE";
            return 0;
        }
    }
    for(int i=2;i<=2*n;i+=2){
        if(dcc[i]<dcc[f(i)]){
            cout<<i<<'\n';
        }else cout<<i-1<<'\n';
    }
    // for(int i=1;i<=n;i++){
    //     cout<<dcc[i]<<" "<<dcc[i+n]<<"\n";
    // }
    return 0;
}