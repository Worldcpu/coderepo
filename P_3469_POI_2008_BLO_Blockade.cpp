#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e5+15;
int n,m,tot,rt,dfn[MN],low[MN],siz[MN];
bool iscut[MN];
ll ans[MN];
vector<int> adj[MN];

void tarjan(int u){
    int ch=0,sum=0;
    siz[u]=1;
    low[u]=dfn[u]=++tot;
    for(auto v:adj[u]){
        if(!dfn[v]){
            tarjan(v);
            siz[u]+=siz[v];
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                ch++;
                sum+=siz[v];
                ans[u]+=1ll*siz[v]*(n-siz[v]);
                if(u!=rt||ch>1) iscut[u]=1;
            }
        }else low[u]=min(low[u],dfn[v]);
    }
    if(iscut[u]){
        ans[u]+=1ll*(n-sum-1)*(sum+1)+n-1;
    }else{  ans[u]=2*(n-1);}
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    rt=1;
    tarjan(1);
    for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
    return 0;
}