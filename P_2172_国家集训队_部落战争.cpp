#include<bits/stdc++.h>
using namespace std;
const int MN=1e6,INF=1e9;
int m,n,r,c,match[MN];
char mapp[55][55];
vector<int> adj[MN];
bool vis[MN];

int getpos(int x,int y){
    return (x-1)*m+y;
}

int dfs(int u){
    for(auto v:adj[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!match[v]||dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    cin>>n>>m>>r>>c;
    int dx[4]={r,r,c,c};
    int dy[5]={c,-c,r,-r};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mapp[i][j];
        }
    }
    int tot=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mapp[i][j]=='.'){
                tot++;
                int nw=getpos(i,j);
                for(int k=0;k<4;k++){
                    int ni=i+dx[k],nj=j+dy[k];
                    if(ni<1||ni>n||nj<1||nj>m||mapp[ni][nj]=='x') continue;
                    int ne=getpos(ni,nj);
                    adj[nw].push_back(ne);
                }
            }
        }
    }
    int ret=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mapp[i][j]=='.'){
                memset(vis,0,sizeof(vis));
                ret+=dfs(getpos(i,j));
            }
        }
    }
    cout<<tot-ret;
    return 0;
}
