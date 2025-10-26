#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
};
int n,p[MN],v[MN],lsanp[MN],lsanv[MN],ptot,vtot,rt,evendg;
bool vis[MN];
vector<Edge> adj[MN];

namespace DSU{
    int pre[MN];
    
    int root(int x){
        if(pre[x]==x) return pre[x];
        return pre[x]=root(pre[x]);
    }

    bool issame(int x,int y){
        return (x==y||root(x)==root(y));
    }

    bool dsumerge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return 1;
        pre[ry]=rx;
        return 0;
    }
}using namespace DSU;

namespace Euler{
    int cur[MN];
    bool vise[MN],vis[MN];
    vector<int> st;

    void dfs(int u){
        for(int i=cur[u];i<adj[u].size();i=max(i+1,cur[u])){
            int v=adj[u][i].v;
            if(!vise[adj[u][i].id]){
                vise[adj[u][i].id]=1;
                cur[u]=i+1;
                dfs(v);
                st.push_back(adj[u][i].id);
            }
        }
    }

}

void init(){
    for(int i=1;i<=ptot+vtot;i++){
        adj[i].clear();
        Euler::cur[i]=Euler::vis[i]=vis[i]=0;
    }
    for(int i=1;i<=n;i++){
        Euler::vise[i]=0;
    }
    ptot=vtot=evendg=rt=0;
    Euler::st.clear();   
    
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>v[i]>>p[i];
        lsanp[++ptot]=p[i];
        lsanv[++vtot]=v[i];
    }

    sort(lsanp+1,lsanp+1+ptot);
    sort(lsanv+1,lsanv+1+vtot);
    ptot=unique(lsanp+1,lsanp+1+ptot)-lsanp-1;
    vtot=unique(lsanv+1,lsanv+1+vtot)-lsanv-1;
    for(int i=1;i<=n;i++){
        p[i]=lower_bound(lsanp+1,lsanp+1+ptot,p[i])-lsanp;
        v[i]=lower_bound(lsanv+1,lsanv+1+vtot,v[i])-lsanv;
    }
    for(int i=1;i<=ptot+vtot+1;i++){
        pre[i]=i;
        vis[i]=0;
    }
    
    for(int i=1;i<=n;i++){
        adj[p[i]].push_back({v[i]+ptot,i});
        adj[v[i]+ptot].push_back({p[i],i});
dsumerge(p[i],v[i]+ptot);
        vis[p[i]]=1;       
        vis[v[i]+ptot]=1;
    }
    for(int i=1;i<=ptot+vtot;i++){
        if(vis[i]) rt=i;
    }
    for(int i=1;i<=ptot+vtot;i++){
        if(vis[i]&&!issame(i,rt)){
            cout<<"No\n";
            return;
        }       
    }
    for(int i=1;i<=ptot+vtot;i++){
        if(adj[i].size()&1){
            rt=i;
            evendg++;
        }
    }
    if(evendg>2){
        cout<<"No\n";
        return;
    }
    cout<<"Yes\n";
    Euler::dfs(rt);
    for(auto p:Euler::st) cout<<p<<' ';
    cout<<'\n';
    cerr<<"QWQ\n";
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}