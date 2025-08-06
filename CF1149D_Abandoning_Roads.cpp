#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520,MK=20;
struct Node{
    int val,pos,st;

    friend bool operator<(const Node &x,const Node &y){
        return x.val<y.val;
    }

};
int n,m,a,b,ktot,lim,bel[MN],f[MN][1<<MK],siz[MN],mp[MN][MN];
bool vis1[MN],vis2[MN],vis[MN][1<<MK];

int dfs1(int u){
    vis1[u]=1;
    int sz=1;
    for(int i=1;i<=n;i++){
        if(!vis1[i]&&mp[u][i]==a){
            sz+=dfs1(i);
        }
    }
    return sz;
}

void dfs2(int u,int ktot){
    bel[u]=ktot;
    siz[ktot]++;
    vis2[u]=1;
    for(int i=1;i<=n;i++){
        if(!vis2[i]&&mp[u][i]==a) dfs2(i,ktot);
    }
}

void dijk(){
    memset(f,0x3f,sizeof(f));
    f[1][0]=0;
    priority_queue<Node,vector<Node>,greater<Node>> q;
    q.push({0,1,0});
    while(!q.empty()){
        auto fr=q.top();
        q.pop();
        int u=fr.pos,st=fr.st;
        if(vis[u][st]) continue;
        vis[u][st]=1;
        int nst=st;
        for(int v=1;v<=n;v++){
            if(bel[u]==bel[v]||bel[v]&&(st>>bel[v])&1) continue;
            if(bel[v]&&bel[u]!=bel[v]) nst|=(1<<bel[v]);
            if(f[v][nst]>f[u][st]+mp[u][v]){
                f[v][nst]=f[u][st]+mp[u][v];
                q.push({f[v][nst],v,nst});
            }
        }
    }
}

int main(){
    cin>>n>>m>>a>>b;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        mp[u][v]=mp[v][u]=w;
    }
    for(int i=1;i<=n;i++){
        if(dfs1(i)>=4){
            dfs2(i,ktot++);
        }
    }
    memset(vis1,0,sizeof(vis1));
    memset(vis2,0,sizeof(vis2));
    lim=ktot;
    for(int i=1;i<=n;i++){
        if(dfs1(i)<4){
            dfs2(i,ktot++);
        }
    }
    dijk();


    return 0;
}
