#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
struct Edge{
    int v,w;
};
struct Node{
    int u,dis;
};
int n,a[MN],ans;
vector<Edge> adj[MN];
vector<Node> vct;

namespace DFZ{
    int siz[MN],maxp[MN],rt,sum,dis[MN],w[MN],ttot1,ttot2;
    int tmp1[MN],tmp2[MN],ret1[MN],ret2[MN],rtot1,rtot2;
    bool vis[MN];

    void getrt(int u,int pre){
        siz[u]=1;
        maxp[u]=0;
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==pre||vis[v]) continue;
            getrt(v,u);
            siz[u]+=siz[v];
            maxp[u]=max(maxp[u],siz[v]);
        }
        maxp[u]=max(maxp[u],sum-siz[u]);
        if(maxp[u]<maxp[rt]) rt=u;
    }

    void dfs(int u,int pre,int mx,int mn){
        if(w[u]-dis[u]>=mx){
            tmp1[++ttot1]=w[u]-dis[u];
        }
        tmp2[++ttot2]=mn;
        for(auto e:adj[u]){
            int v=e.v;
            if(vis[v]||v==pre) continue;
            dis[v]=dis[u]+e.w;
            w[v]=w[u]+a[v];
            dfs(v,u,max(mx,w[u]-dis[u]),min(mn,w[u]-dis[v]));
        }
    }

    void calc(int u){
        rtot1=rtot2=0;
        dis[u]=0;
        w[u]=a[u];
        for(auto e:adj[u]){
            int v=e.v;
            if(vis[v]) continue;
            dis[v]=e.w;
            w[v]=w[u]+a[v];
            ttot1=ttot2=0;
            dfs(v,u,w[u]-dis[u],w[u]-dis[v]);
            sort(tmp1+1,tmp1+1+ttot1);
            sort(tmp2+1,tmp2+1+ttot2);
            int l=1;
            for(int i=ttot2;i>=1;i--){
                while(l<=ttot1&&tmp1[l]+tmp2[i]-a[u]<0) l++;
                ans-=ttot1-l+1;
            }
            for(int i=1;i<=ttot1;i++){
                ret1[++rtot1]=tmp1[i];
            }
            for(int i=1;i<=ttot2;i++){
                ret2[++rtot2]=tmp2[i];
            }
        }
        sort(ret1+1,ret1+1+rtot1);
        sort(ret2+1,ret2+1+rtot2);
        int l=1;
        for(int i=rtot2;i>=1;i--){
            if(ret2[i]>=0) ans++;
            while(l<=rtot1&&ret1[l]+ret2[i]-a[u]<0) l++;
            ans+=rtot1-l+1;
        }
        ans+=rtot1;
    }

    void solve(int u){
        vis[u]=1;
        calc(u);
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(vis[v]) continue;
            sum=siz[v];
            maxp[rt=0]=INF;
            getrt(v,0);
            solve(rt);
        }
    }

}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    DFZ::maxp[DFZ::rt=0]=DFZ::sum=n;
    DFZ::getrt(1,0);
    DFZ::getrt(DFZ::rt,0);
    DFZ::solve(DFZ::rt);
    cout<<ans;
    return 0;
}