#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
struct Node{
    int u,v,w;
};
int n,K,rt,mn,mx;
vector<int> adj[MN];
set<pir> st,srt[MN];

namespace Tree{
    int siz[MN],dep[MN],maxp[MN],dg[MN],htop[MN],fa[MN],dfn[MN],cur[MN],dtot;
    bool vis[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        maxp[u]=0;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            maxp[u]=max(maxp[u],siz[v]);
        }
        maxp[u]=max(maxp[u],n-siz[u]);
        if(maxp[u]<maxp[rt]) rt=u;
    }

    void getrt(){
        rt=0;
        for(int i=1;i<=n;i++){
            siz[i]=maxp[i]=0;
        }
        maxp[rt]=n;
        dfs1(1,0);
        for(int i=1;i<=n;i++){
            siz[i]=maxp[i]=0;
        }
    }

    void dfs2(int u,int pre,int rt){
        siz[u]=1;
        dep[u]=dep[pre]+1;
        htop[u]=rt;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dg[u]++;
            dfs2(v,u,rt);
            siz[u]+=siz[v];
        }
        mn+=siz[u]&1;       
        mx+=siz[u];
        if(dg[u]) srt[rt].insert(pir(dep[u],u));
    }

    void dfs3(int u){
        if(!vis[u]) dfn[++dtot]=u;
        for(auto v:adj[u]){
            if(v==fa[u]) continue;
            dfs3(v); 
        }
    }

    void del(int u){
        vis[u]=1;
        if(!--dg[fa[u]]){
            srt[htop[fa[u]]].erase(pir(dep[fa[u]],fa[u]));
        }
    }

    void match(int u){
        int p[5]{},cnt=0;
        for(int &i=cur[u];i<adj[u].size();i++){
            int v=adj[u][i];
            if(cnt==2) break;
            if(v==fa[u]) continue;
            if(!vis[v]) p[++cnt]=v;
        }
        if(!vis[u]) p[++cnt]=u;
        cout<<p[1]<<' '<<p[2]<<'\n';
        assert(cnt>=2);
        del(p[1]);
        del(p[2]);
    }

}

signed main(){
    cin>>n>>K;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Tree::getrt();
    for(auto v:adj[rt]){
        Tree::dfs2(v,rt,v);
        if(Tree::siz[v]>1) st.insert(pir(Tree::siz[v],v));
    }
    if(K>mx||K<mn||K%2!=mx%2){
        cout<<"NO\n";
        return 0;
    }
    cout<<"YES\n";
    mx=mx-K;
    while(mx){
        auto x=(*st.rbegin()).second,y=(*srt[x].rbegin()).second;
        st.erase(pir(Tree::siz[x],x));
        if(mx<=2*Tree::dep[y]){
            y=(*srt[x].lower_bound(pir(mx/2,0))).second;
            Tree::match(y);
            break;
        }
        mx-=2*Tree::dep[y];
        Tree::siz[x]-=2;
        Tree::match(y);
        if(Tree::siz[x]>1) st.insert(pir(Tree::siz[x],x));
    }
    Tree::dfs3(rt);
    using namespace Tree;
    for(int i=1;i<=dtot/2;i++){
        cout<<dfn[i]<<' '<<dfn[i+Tree::dtot/2]<<'\n';
    }
    return 0;
}