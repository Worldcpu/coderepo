#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e4+15,ML=20;
struct Edge{
    int v,w;
};
int n,m,pos[MN],ndtot,ltot,tot,dep[MN],fa[MN][30],dis[MN][30],ndis[MN],dg[MN],last[MN],sumw;
bool vis[MN],need[MN],isok;
pir jd[MN];
vector<Edge> adj[MN];

void dfs(int u,int pre,int w){
    fa[u][0]=pre;
    dis[u][0]=w;
    dep[u]=dep[pre]+1;
    for(int i=1;i<=ML;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
        dis[u][i]=dis[u][i-1]+dis[fa[u][i-1]][i-1];
    }
    for(auto e:adj[u]){
        if(e.v==pre) continue;
        dfs(e.v,u,e.w);
    }
}

bool dfs2(int u){
    if(vis[u]) return 1;
    if(adj[u].size()==1) return 0;
    for(auto e:adj[u]){
        if(dep[e.v]<dep[u]) continue;
        if(!dfs2(e.v)) return 0;
    }
    return 1;
}

bool check(int k){
    ndtot=ltot=tot=0;
    memset(vis,0,sizeof(vis));
    memset(need,0,sizeof(need));
    for(int i=1;i<=m;i++){
        int u=pos[i],rest=0;
        for(int j=ML;j>=0;j--){
            if(fa[u][j]>1&&rest+dis[u][j]<=k){
                rest+=dis[u][j];
                u=fa[u][j];
            }
        }
        if(fa[u][0]==1&&rest+dis[u][0]<=k) jd[++tot]=pir(k-rest-dis[u][0],u);
        else vis[u]=1;
    }
    for(auto e:adj[1]){
        if(!dfs2(e.v)) need[e.v]=1;
    }
    sort(jd+1,jd+1+tot);
    for(int i=1;i<=tot;i++){
        if(need[jd[i].second]&&jd[i].first<dis[jd[i].second][0]) need[jd[i].second]=0;
        else last[++ltot]=jd[i].first;
    }
    for(auto e:adj[1]){
        if(need[e.v]){
            ndis[++ndtot]=e.w;
        }
    }
    sort(last+1,last+1+ltot);
    sort(ndis+1,ndis+1+ndtot);
    int i,j;
    for(i=1,j=1;i<=ltot&&j<=ndtot;){
        if(last[i]>=ndis[j]) i++,j++;
        else i++;
    }
    if(j>ndtot) return isok=1;
    else return 0;
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        sumw+=w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        dg[u]++;
        dg[v]++;
    }
    dfs(1,0,0);
    cin>>m;
    if(dg[1]>m){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=m;i++){
        cin>>pos[i];
    }
    int l=0,r=sumw;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid;
    }
    if(!isok) cout<<-1;
    else cout<<r;
    return 0;
}