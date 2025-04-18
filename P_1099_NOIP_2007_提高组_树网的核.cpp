#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=350;
struct Edge{
    int v,w;
};
struct Node{
    int u,fa,len,prew;
};
int n,s,fa[MN],fr[MN],dep[MN],bk[MN],mxdep;
vector<Edge> adj[MN];
vector<int> zj;
bool vis[MN];
unordered_map<int,int> posn;

void dfs(int u,int pre){
    fa[u]=pre;
    for(auto e:adj[u]){
        if(e.v==pre||vis[e.v]) continue;
        dep[e.v]=dep[u]+e.w;
        if(dep[e.v]>dep[mxdep]) mxdep=e.v;
        dfs(e.v,u);
    }
}

int main(){
    cin>>n>>s;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs(1,0);
    dep[mxdep]=0;
    dfs(mxdep,0);
    for(int i=mxdep;i;i=fa[i]){
        vis[i]=1;
        zj.push_back(i);
        bk[zj.size()-1]=dep[i];
    }
    reverse(zj.begin(),zj.end());
    for(int i=zj.size()-1;i>=0;i--){
        fr[i]=bk[zj.size()-1]-bk[i];
    }
    int maxx=0,ans=1e9;
    for(auto p:zj){
        dep[p]=0;
        mxdep=0;
        dfs(p,0);
        maxx=max(maxx,dep[mxdep]);
    }
    for(int l=0,r=0;l<zj.size();l++){
        while(r<zj.size()-1&&bk[r+1]-bk[l]<=s){
            r++;
        }
        ans=min(ans,max({maxx,bk[l],fr[r]}));
    }
    cout<<ans;


    return 0;
}