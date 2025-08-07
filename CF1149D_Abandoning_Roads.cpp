#include<bits/stdc++.h>
using namespace std;
constexpr int MN=75,MK=20;
struct Node{
    int val,pos,st;

    friend bool operator>(const Node &x,const Node &y){
        return x.val>y.val;
    }

};
int n,m,a,b,ktot,bel[MN],f[MN][1<<MK],siz[MN],mp[MN][MN];
bool vis1[MN],vis2[MN];

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

void dfs2(int u,int ktot,int op){
    bel[u]=ktot;
    siz[ktot]++;
    vis2[u]=op;
    for(int i=1;i<=n;i++){
        if(!bel[i]&&mp[u][i]==a) dfs2(i,ktot,op);
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
        if(fr.val>f[u][st]) continue;
        for(int v=1;v<=n;v++){
            if(mp[u][v]==0) continue;
            int nst=st;
            if((bel[u]==bel[v]&&mp[u][v]!=a)||(vis2[v]&&((st>>bel[v])&1))) continue;
            if(vis2[u]&&bel[u]!=bel[v]) nst|=(1<<bel[u]);
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
        if(!bel[i]&&dfs1(i)>=4){
            dfs2(i,++ktot,1);
        }
    }
    memset(vis1,0,sizeof(vis1));
    for(int i=1;i<=n;i++){
        if(!bel[i]&&dfs1(i)<4){
            dfs2(i,++ktot,0);
        }
    }
    for(int i=1;i<=n;i++) bel[i]--;
    dijk();
    for(int i=1;i<=n;i++){
        int ret=f[i][0];
        for(int j=1;j<(1<<18);j++){
            ret=min(ret,f[i][j]);
        }
        cout<<ret<<' ';
    }


    return 0;
}
