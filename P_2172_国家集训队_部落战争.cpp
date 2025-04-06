#include<bits/stdc++.h>
using namespace std;
const int MN=114514,INF=1e9;
int s,t,m,n,r,c,cur[MN],dep[MN];
char mapp[MN][MN];
struct edge
{
    int v,len,id;
};
vector<edge> adj[MN];
void add(int u,int v,int c){
    int uz=adj[u].size(),vz=adj[v].size();
    adj[u].push_back({v,c,vz});
    adj[v].push_back({u,0,uz});
}
int getpos(int x,int y){
    return (x-1)*n+y;
}
bool bfs(){
    queue<int> q;
    memset(dep,-1,sizeof(dep));
    dep[s]=0;
    q.push(s);
    while (!q.empty())
    {
        int f=q.front();
        q.pop();
        for(auto e:adj[f]){
            int v=e.v;
            if(dep[v]==-1&&e.len){
                dep[v]=dep[f]+1;
                q.push(v);
            }
        }
    }
    return (dep[t]!=-1);
}
int dfs(int u,int limit){
    if(u==t){
        return limit;
    }
    for(int &i=cur[u];i<adj[u].size();i++){
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&adj[u][i].len){
            int p=dfs(v,min(limit,adj[u][i].len));
            if(p){
                adj[u][i].len-=p;
                adj[v][adj[u][i].id].len+=p;
                return p;
            }else dep[v]=-1;
        }
    }
    return 0;
}
int dinic(){
    int ans=0,flow;
    while (bfs())
    {
        memset(cur,0,sizeof(cur));
        while (flow=dfs(s,INF))
        {
            ans+=flow;
        }
        
    }
    return ans;   
}
int main(){
    cin>>n>>m>>r>>c;
    s=n*m*2+1,t=n*m*2+2;
    int dx[5]={r,-r,c,-c};
    int dy[5]={c,c,r,r};
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
                add(s,nw,1);
                add(nw+n*m,t,1);
                for(int k=0;k<4;k++){
                    int ni=i+dx[k],nj=j+dy[k];
                    if(ni<1||ni>n||nj<1||nj>m||mapp[ni][nj]=='x') continue;
                    int ne=getpos(ni,nj);
                    add(nw,ne+n*m,1);
                }
            }
        }
    }
    cout<<tot-dinic();
    return 0;
}