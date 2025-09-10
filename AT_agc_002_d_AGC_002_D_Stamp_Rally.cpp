#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,ML=18;
struct Edge{int u,v,w;}e[MN];
int n,m,pre[MN],val[MN],dtot,q;
vector<int> adj[MN];
namespace Tree{
    int fa[ML][MN],dep[MN],leaf[MN];
    void dfs(int u,int p){
        fa[0][u]=p;dep[u]=dep[p]+1;
        for(auto v:adj[u]) if(v!=p) dfs(v,u),leaf[u]+=leaf[v];
    }
    void initfa(int dt){
        for(int i=1;i<ML;i++) for(int j=1;j<=dt;j++) fa[i][j]=fa[i-1][fa[i-1][j]];
    }
}using namespace Tree;
int root(int x){return pre[x]==x?x:pre[x]=root(pre[x]);}
void exkru(){
    dtot=n;
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru!=rv){
            ++dtot;pre[ru]=pre[rv]=dtot;val[dtot]=i;
            adj[dtot].push_back(ru);adj[dtot].push_back(rv);
            if(dtot==2*n-1) break;
        }
    }
}
void initpre(){
    for(int i=0;i<MN;i++) pre[i]=i;
}
int check(int x,int y,int k){
    for(int i=ML-1;i>=0;i--){
        if(val[fa[i][x]]<=k) x=fa[i][x];
        if(val[fa[i][y]]<=k) y=fa[i][y];
    }
    if(x==y) return leaf[x]; else return leaf[x]+leaf[y];
}
int main(){
    initpre();cin>>n>>m;val[0]=1e9;
    for(int i=1;i<=n;i++) leaf[i]=1;
    for(int i=1;i<=m;i++) cin>>e[i].u>>e[i].v;
    exkru();dfs(dtot,0);initfa(dtot);
    cin>>q;
    while(q--){
        int x,y,z;cin>>x>>y>>z;
        int l=1,r=m,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(x,y,mid)>=z) ans=mid,r=mid-1;
            else l=mid+1;
        }
        cout<<ans<<'\n';
    }
}
