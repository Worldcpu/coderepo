#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,ML=30,MB=500;
int n,R,q,r[MN],id[MN],idtot;
vector<int> adj[MN];
vector<int> col[MN],obl;

namespace Tree{
    int dfn[MN],st[31][MN],dtot;
    
    void dfs1(int u,int pre){
        dfn[u]=++dtot;
        st[0][dfn[u]]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
        }
    }

    int cmpdfn(int x,int y){
        return dfn[x]<dfn[y]?x:y;
    }

    bool scmpdfn(int x,int y){
        return dfn[x]<dfn[y];
    }

    void initst(){
        for(int i=1;i<=ML;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[i][j]=cmpdfn(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }

    int lca(int x,int y){
        if(x==y) return x;
        x=dfn[x],y=dfn[y];
        if(x>y) swap(x,y);
        int lg=__lg(y-x++);
        return cmpdfn(st[lg][x],st[lg][y-(1<<lg)+1]);
    }
}using namespace Tree;

namespace T1{
    int ans[MB+15][MN],cnt[MB+15];
    void dfst1(int u){
        for(int i=1;i<=idtot;i++) ans[i][r[u]]-=cnt[i];
        for(auto v:adj[u]){
            dfst1(v);
        }
        cnt[id[r[u]]]++;
        for(int i=1;i<=idtot;i++) ans[i][r[u]]+=cnt[i];
    }
}

namespace T2{
    
}

int main(){
    cin>>n>>R>>q>>r[1];
    for(int i=2;i<=n;i++){
        int u;
        cin>>u>>r[i];
        adj[u].push_back(i);
        adj[i].push_back(u);
        col[r[i]].push_back(i);
    }
    dfs1(1,0);
    initst();
    for(int i=1;i<=n;i++){
        col[r[i]].push_back(i);
    }
    for(int i=1;i<=R;i++){
        sort(col[i].begin(),col[i].end(),scmpdfn);
    }
    for(int i=1;i<=R;i++){
        if(col[i].size()>MB) id[i]=++idtot; 
    }
    
    
    return 0;
}
