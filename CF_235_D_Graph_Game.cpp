#include<bits/stdc++.h>
#define double long double
using namespace std;
constexpr int MN=3520;
int n;
double ans;
vector<int> adj[MN];

namespace Tree{
    int fa[MN][31],dfn[MN],col[MN],dep[MN],pre[MN],dtot,htot,lp[MN];
    bool oncir[MN];
    
    void dfs1(int u,int pree){
        pre[u]=pree;
        dfn[u]=++dtot;
        for(auto v:adj[u]){
            if(v==pree) continue;
            if(dfn[v]){
                if(dfn[v]<dfn[u]) continue;
                lp[++htot]=v;
                oncir[v]=1;
                for(;v!=u;v=pre[v]) lp[++htot]=pre[v],oncir[pre[v]]=1;
            }else dfs1(v,u);
        }
    }
    
    void dfs2(int u,int pree,int c){
        col[u]=c;
        dep[u]=dep[pree]+1;
        fa[u][0]=pree;
        for(int i=1;i<=30;i++){
            fa[u][i]=fa[fa[u][i-1]][i-1];
        }
        for(auto v:adj[u]){
            if(v==pree||oncir[v]) continue;
            dfs2(v,u,c);
        }
    }

    int lca(int x,int y){
        if(dep[x]>dep[y]) swap(x,y);
        for(int i=20;i>=0;i--){
            if(dep[fa[y][i]]>=dep[x]) y=fa[y][i];
        }
        if(x==y) return x;
        for(int i=__lg(dep[x]);i>=0;i--){
            if(fa[x][i]!=fa[y][i]){
                x=fa[x][i],y=fa[y][i];
            }
        }
        return fa[x][0];
    }

    int getdis(int x,int y){
        return dep[x]+dep[y]-2*dep[lca(x,y)]+1;
    }

}using namespace Tree;


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int u,v;
        cin>>u>>v;
        ++u,++v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Tree::dfs1(1,0);
    for(int i=1;i<=htot;i++){
        dfs2(lp[i],0,i);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(col[i]==col[j]){
                ans+=1.0/getdis(i,j);
            }else{
                int rtd=dep[i]+dep[j],ld=abs(col[i]-col[j])-1,rd=htot-2-ld;
                ans+=1.0/(rtd+ld)+1.0/(rtd+rd)-1.0/(rtd+ld+rd);
            }
        }
    }
    cout<<fixed<<setprecision(15)<<ans;
    return 0;
}