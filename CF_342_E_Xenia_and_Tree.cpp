#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
struct Query{
    int op,x;
}qry[MN];
int n,q,blen,mndis[MN],dis[MN],pos[MN];
vector<int> adj[MN];

namespace Tree{
    int dep[MN],siz[MN],hson[MN],htop[MN],fa[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]= (pre==0 ? 0 : dep[pre]+1 ); 
        siz[u]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop); 
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]){
                swap(x,y);
            }
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

    int gdis(int x,int y){
        return dep[x]+dep[y]-(dep[lca(x,y)]<<1);
    }

}using namespace Tree;

void bfs(int idx){
    queue<int> que;
    for(int i=1;i<=n;i++){
        dis[i]=1e9;
    }
    for(int i=max(1ll,idx-blen);i<idx;i++){
        if(qry[i].op==1){
            que.push(qry[i].x);
            dis[qry[i].x]=0;
        }
    }
    while(!que.empty()){
        int u=que.front(); que.pop();
        for(auto v:adj[u]){
            if(dis[v]>dis[u]+1){
                dis[v]=dis[u]+1;
                que.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++){
        mndis[i]=min(mndis[i], (int)dis[i]);
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>q;
    blen=sqrt(n);
    pos[0]=1;
    for(int i=1;i<=q;i++){
        pos[i]=(i-1)/blen+1;
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        mndis[i]=dep[i]; 
    }
    for(int i=1;i<=q;i++){
        cin>>qry[i].op>>qry[i].x;
    }
    for(int i=1;i<=q;i++){
        if(pos[i]!=pos[i-1]){
            bfs(i);
        }
        if(qry[i].op==2){
            int ans=mndis[qry[i].x];
            for(int j=i-1;j&&pos[j]==pos[i];j--){
                if(qry[j].op==1) ans=min(ans,(int)gdis(qry[i].x,qry[j].x));
            }
            cout<<ans<<'\n';
        }
    }
    return 0;
}
