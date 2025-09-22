#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
};
int dg[MN],n,m,t,tmp[MN],etot,eu[MN],ev[MN],dtot;
unordered_map<int,unordered_map<int,bool>> vis;
unordered_map<int,int> mp;
vector<Edge> G[MN],g[MN],adj[MN];
vector<int> st,evct[MN];

namespace DSU{
    int pre[MN];

    void initpre(){
        for(int i=1;i<MN;i++){
            pre[i]=i;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }
}using namespace DSU;

namespace Euler{
    int cur[MN],in[MN];
    bool vise[MN],visd[MN];

    void dfs(int u){
        if(!visd[u]) visd[u]=1,++dtot;
        while(cur[u] < adj[u].size()){
            auto e=adj[u][cur[u]++];
            if(!vise[e.id]){
                vise[e.id]=1;
                dfs(e.v);
                if(e.id>m) st.push_back(e.id);
            }
        }
        st.push_back(u);
    }
}using namespace Euler;

int gethsh(int u,int v){
    return u*MN+v;
}

void nosol(){
    cout<<"NIE\n";
    exit(0);
}

signed main(){
    initpre();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        eu[i]=u,ev[i]=v;
        g[u].push_back({v,i});
        mp[gethsh(u,v)]=i;
    }
    cin>>t;
    for(int i=1;i<=t;i++){
        int K;
        cin>>K;
        for(int j=1;j<=K;j++){
            cin>>tmp[j];
        }
        for(int j=1;j+1<K;j++){
            int u=mp[gethsh(tmp[j],tmp[j+1])],v=mp[gethsh(tmp[j+1],tmp[j+2])];
            if(!u||!v) nosol();
            if(vis[u][v]) continue;
            if(G[u].size()||dg[v]||root(u)==root(v)) nosol();
            vis[u][v]=1;
            G[u].push_back({v,0});  
            dg[v]++;
            pre[root(u)] = root(v); 
        }
    }
    etot = m;
    for(int i=1;i<=m;i++){
        if(dg[i]||!G[i].size()) continue;
        ++etot;
        int p=i;
        while(1){
            if(!G[p].size()) break;
            evct[etot].push_back(ev[p]);
            p=G[p][0].v;
        }
        adj[eu[i]].push_back({ev[p],etot});
    }
    for(int i=1;i<=n;i++){
        for(auto e:g[i]){
            if(!dg[e.id]&&G[e.id].empty()){
                adj[i].push_back(e);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(auto e:adj[i]){
            in[e.v]++;
        }
    }
    for(int i=1;i<=n;i++){
        if(in[i]!=adj[i].size()) nosol();
        else if(adj[i].size()==0) dtot++;
    }
    if(!adj[1].size()) nosol();
    dfs(1);
    if(dtot!=n){
        nosol();
    }
    cout<<"TAK\n";
    reverse(st.begin(),st.end());
    for(auto p:st){
        if(p>m){
            for(auto qwq:evct[p]){
                cout<<qwq<<'\n';
            }
        }else cout<<p<<'\n';
    }
    return 0;
}
