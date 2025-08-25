#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
struct Edge{
    int v,w;
};
int n,rt,S,T,q,ans,disa[MN],disb[MN],dis[MN],sum[MN];
vector<Edge> adj[MN];

namespace Tree{
    vector<int> val,pos;

    void dfs1(int u,int pre,int dis[]){
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==pre) continue;
            dis[v]=dis[u]+e.w;
            dfs1(v,u,dis);
        }
    }

    void dfs2(int u,int pre,int x){
        val.push_back(dis[u]);
        pos.push_back(u);
        sum[u]=1;
        sum[pos[lower_bound(val.begin(),val.end(),dis[u]-x)-val.begin()-1]]--;
        for(auto e:adj[u]){
            int v=e.v;
            if(v==pre) continue;
            dfs2(v,u,x);
            sum[u]+=sum[v];
        }
        ans=max(ans,sum[u]);
        val.pop_back();
        pos.pop_back();
    }

}using namespace Tree;

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs1(1,0,disa);
    for(int i=1;i<=n;i++){
        if(disa[i]>disa[S]) S=i;
    }
    memset(disa,0,sizeof(disa));
    dfs1(S,0,disa);
    for(int i=1;i<=n;i++){
        if(disa[i]>disa[T]) T=i;
    }
    dfs1(T,0,disb);
    rt=1;
    for(int i=1;i<=n;i++){
        dis[i]=max(disa[i],disb[i]);
        if(dis[i]<dis[rt]){
            rt=i;
        }
    }
    val.push_back(-INF);
    pos.push_back(0);
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        ans=0;       
        dfs2(rt,0,x);
        cout<<ans<<'\n';
    }

    
    return 0;
}