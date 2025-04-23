#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,fa[MN],f[MN][2];
bool vis[MN];
vector<int> adj[MN];

int dodp(int u,int mode,int rt){
    f[u][0]=f[u][1]=0;
    vis[u]=1;
    int minp=1e9;
    for(auto v:adj[u]){
        if(v==rt) continue;
        int ret=dodp(v,mode,rt);
        minp=min(minp,ret-f[v][0]);
        f[u][0]+=ret;
    }
    f[u][1]=f[u][0]+1-(mode&&u==fa[rt]?0:minp);
    return max(f[u][0],f[u][1]);
}

int getlp(int u){
    vis[u]=1;
    if(vis[fa[u]]) return u;
    else return getlp(fa[u]);

}

int solve(int u){
    int lp=getlp(u);
    int ret1=dodp(lp,0,lp),ret2=dodp(lp,1,lp);
    return max(ret1,f[lp][0]);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>fa[i];
        adj[fa[i]].push_back(i);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!vis[i]) ans+=solve(i);
    }
    cout<<ans;
    return 0;
}