#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int v,id;
};
int n,m,rt,crt,bid,c[MN],id[MN],ans[MN];
vector<Edge> adj[MN];



namespace Tree{
    int dep[MN],fa[MN],cir[MN],cid[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(!dep[v]) dfs1(v,u);
            if(!crt&&dep[v]&&(dep[u]-dep[v]+1)%2==1){
                rt=u;
                crt=v;
                bid=id;
                for(int i=u;i!=v;i=fa[i]) cir[i]=fa[i];
            }
        }
    }

    void dfs2(int u,int pre){
        dep[u]=dep[pre]+1;
        fa[u]=pre;
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(e.v==cir[u]&&!dep[v]&&id!=bid){
                cid[v]=id;
                dfs2(v,u);
            }
        }
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(!dep[v]&&id!=bid){
                cid[v]=id;
                dfs2(v,u);
            }
        }
        ans[cid[u]]=c[u];
        c[fa[u]]-=ans[cid[u]];
    }

}using namespace Tree;



signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    dfs1(rt=1,0);
    memset(dep,0,sizeof(dep));
    dfs2(rt,0);
    if(crt){
        int dx=c[rt]/2;
        c[rt]%=2;
        ans[bid]+=dx;
        for(int i=-dx;crt!=rt;i=-i){
            ans[cid[crt]]+=i;
            crt=fa[crt];
        }
    }
    if(c[rt]){
        cout<<"NO";
        return 0;
    }
    cout<<"YES\n";
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}