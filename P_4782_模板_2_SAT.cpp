#include<iostream>
#include<vector>
using namespace std;
const int MN=2*1e6+15;
int n,m,dfn[MN],low[MN],vdcc[MN],tot,dcc;
vector<int> adj[MN];
bool vis[MN];
int s[MN],top;
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
        dcc++;
        int t;
        while (s[top]!=u)
        {
            vdcc[s[top]]=dcc;
            vis[s[top]]=0;
            top--;
        }
        vdcc[s[top]]=dcc;
        vis[s[top]]=0;
        top--;
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int xi,a,xj,b;
        cin>>xi>>a>>xj>>b;
        int ni=xi+n,nj=xj+n;
        if(a==0&&b==0){
            adj[ni].push_back(xj);//a=1则b=0
            adj[nj].push_back(xi);//b=1则a=0
        }
        if(a==1&&b==0){
            adj[xi].push_back(xj);//a=0则b=0
            adj[nj].push_back(ni);//b=1则a=1
        }
        if(a==0&&b==1){
            adj[ni].push_back(nj);//a=1则b=1
            adj[xj].push_back(xi);//b=0则a=0
        }
        if(a==1&&b==1){
            adj[xi].push_back(nj);//a=0 b=1
            adj[xj].push_back(ni);//b=0 a=1
        }
    }
    for(int i=1;i<=n*2;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(vdcc[i]==vdcc[i+n]){
            cout<<"IMPOSSIBLE";
            return 0;
        }
    }
    cout<<"POSSIBLE"<<endl;
    for(int i=1;i<=n;i++){
        //强联通分量编号越小 -> 拓扑序越大 -> 越优
        cout<<(vdcc[i]>vdcc[i+n])<<" ";
    }
    return 0;
}