#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f,MT=1e3;
int n,A,B,a[MN],b[MN],ctot,ans,all,Ctot;
char mp[MT][MT];

namespace FYDinic{
    struct Edge{
        int v,w,c,id;
    };
    int cur[MN],dis[MN],mncst,S,T;
    bool vis[MN];
    vector<Edge> adj[MN];

    void add(int u,int v,int w,int c){
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,w,c,vs});
        adj[v].push_back({u,0,-c,us});
    }

    bool spfa(int S,int T){
        memset(dis,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        queue<int> q;
        q.push(S);
        dis[S]=0;
        vis[S]=1;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(auto e:adj[u]){
                if(e.w&&dis[e.v]>dis[u]+e.c){
                    dis[e.v]=dis[u]+e.c;
                    if(!vis[e.v]){
                        vis[e.v]=1;
                        q.push(e.v);
                    }
                }
            }
        }
        memset(cur,0,sizeof(cur));
        return (dis[T]!=INF);
    }

    int dfs(int u,int lim,int T){
        if(u==T) return lim;
        int ret=0;
        vis[u]=1;
        for(int &i=cur[u];i<adj[u].size();i++){
            int v=adj[u][i].v;
            if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].c){
                int p=dfs(v,min(lim,adj[u][i].w),T);
                if(p){
                    adj[u][i].w-=p;
                    adj[v][adj[u][i].id].w+=p;
                    ret+=p;
                    lim-=p;
                    mncst+=p*adj[u][i].c;
                    if(!lim) break;
                }else dis[v]=INF;
            }
        }
        vis[u]=0;
        return ret;
    }

    int dinic(int S,int T){
        int ans=0;
        mncst=0;
        while(spfa(S,T)){
            ans+=dfs(S,INF,T);
        }
        return ans;
    }
}using namespace FYDinic;

void initgraph(){
    for(int i=0;i<=T;i++){
        adj[i].clear();
    }
}

void build(int k){
    initgraph();
    all=0;
    for(int i=1;i<=n;i++){
        all+=a[i];
        add(S,i,a[i],0);
        add(i+n,T,b[i],0);
        add(i,i+n,k,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mp[i][j]=='.'){
                add(i,j+n,1,1);
            }
        }
    }
    int mxflow=dinic(S,T);
    if(mxflow==all&&k*B<=(mxflow-mncst)*A){
        ans=max(ans,mxflow-mncst);
    }
}

void init(){
    S=0,T=2*n+1;
    ans=-1;
    ctot=0;
    for(int i=1;i<=n;i++){
        a[i]=b[i]=0;
    }
}

void solve(){
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>mp[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i]+=(mp[i][j]=='C'||mp[i][j]=='.');
            b[j]+=(mp[i][j]=='C'||mp[i][j]=='.');
            ctot+=mp[i][j]=='C';
        }
    }
    for(int i=0;i<=n;i++){
        build(i);
    }
    if(ans==-1) cout<<"impossible\n";
    else cout<<ans-ctot<<'\n';
}

int main(){
    while(cin>>n>>A>>B){
        if(!n&&!A&&!B){
            break;
        }
        cout<<"Case "<<++Ctot<<": ";
        solve();
    }
    return 0;
}