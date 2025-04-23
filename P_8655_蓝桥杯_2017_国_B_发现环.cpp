#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,dfn[MN],lp[MN],fa[MN],htot,tot;
vector<int> adj[MN];

template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

void dfs(int u,int pre){
    dfn[u]=++tot;
    fa[u]=pre;
    for(auto v:adj[u]){
        if(v==pre) continue;
        if(dfn[v]){
            if(dfn[v]<dfn[u]) continue;
            lp[++htot]=v;
            for(;v!=u;v=fa[v]) lp[++htot]=fa[v];	
        }else dfs(v,u);
    }
}

int main(){
    read(n);
    for(int i=1;i<=n;i++){
        int u,v;
        read(u);
        read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    sort(lp+1,lp+1+htot);
    for(int i=1;i<=htot;i++) cout<<lp[i]<<" ";
    return 0;
}