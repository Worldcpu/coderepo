#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,INF=0x3f3f3f3f,MK=150;
struct Edge{
    int v,w,id;
};
int n,m,K,S,T,cur[MN],dep[MN],pre[MN],r[MK],sp[MK][MK],h[MK],maxp=n+2;
vector<Edge> adj[MN];

void add(int u,int v,int w){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,vs});
    adj[v].push_back({u,0,us});
}

inline int gp(int id,int t){
    maxp=max(id+t*(n+1),maxp);
    return id+t*(n+1);
}

bool bfs(){
    for(int i=0;i<=maxp;i++){
        dep[i]=-1;
    }
    dep[T]=-1;
    dep[S]=0;
    queue<int> q;
    q.push(S);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto e:adj[u]){
            if(e.w&&dep[e.v]==-1){
                dep[e.v]=dep[u]+1;
                q.push(e.v);
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dep[T]!=-1);
}

int dfs(int u,int lim){
    if(u==T) return lim;
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&adj[u][i].w){
            int p=dfs(v,min(lim,adj[u][i].w));
            if(p){
                adj[u][i].w-=p;
                adj[v][adj[u][i].id].w+=p;
                return p;
            }else dep[v]=-1;
        }
    }
    return 0;
}

int dinic(){
    int ans=0,flow;
    while(bfs()){
        // cout<<"QWQ\n";
        ans+=dfs(S,INF);
    }
    return ans;
}

inline void initpre(){
    for(int i=1;i<MN;i++) pre[i]=i;
}

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

int main(){
    initpre();
    cin>>n>>m>>K;
    S=0,T=MN-2;
    for(int i=1;i<=m;i++){
        cin>>h[i]>>r[i];
        for(int j=0;j<r[i];j++){
            cin>>sp[i][j];
            if(sp[i][j]==0) sp[i][j]=n+1;
            else if(sp[i][j]==-1) sp[i][j]=n+2;
            if(j!=0){
                pre[root(sp[i][j-1])]=root(sp[i][j]);
            }
        }
    }
    if(root(n+1)!=root(n+2)){
        cout<<0;
        return 0;
    }
    int ans=0;
    for(ans=1;;ans++){
        // if(ans>=7) break;
        add(S,gp(n+1,ans-1),INF);
        for(int i=1;i<=m;i++){
            int x=(ans-1)%r[i],y=(ans)%r[i];
            if(sp[i][x]==n+2) x=T;
            else x=gp(sp[i][x],ans-1);
            if(sp[i][y]==n+2) y=T;
            else y=gp(sp[i][y],ans);
            add(x,y,h[i]);
        }
        int mxflow=dinic();
        // cout<<mxflow<<'\n';
        if(mxflow>=K){
            cout<<ans;
            return 0;
        }
        for(int i=1;i<=n+1;i++){
            add(gp(i,ans-1),gp(i,ans),INF);
        }
    }
    return 0;
}