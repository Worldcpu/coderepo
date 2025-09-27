#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int n,a[MN],dtot,id[MN][4],mx,b[MN];

namespace Dinic{
    struct Edge{
        int v,w,id;
    };
    int S,T,cur[MN],dep[MN];
    vector<Edge> adj[MN];

    void add(int u,int v,int w){
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,w,vs});
        adj[v].push_back({u,0,us});
    }

    bool bfs(int S,int T){
        memset(dep,-1,sizeof(dep));
        queue<int> q;
        dep[S]=0;
        q.push(S);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto e:adj[u]){
                if(dep[e.v]==-1&&e.w){
                    dep[e.v]=dep[u]+1;
                    q.push(e.v);
                }
            }
        }
        memset(cur,0,sizeof(cur));
        return (dep[T]!=-1);
    }

    int dfs(int u,int lim,int T){
        if(u==T) return lim;
        for(int &i=cur[u];i<adj[u].size();i++){
            int v=adj[u][i].v;
            if(dep[v]==dep[u]+1&&adj[u][i].w){
                int p=dfs(v,min(lim,adj[u][i].w),T);
                if(p){
                    adj[u][i].w-=p;
                    adj[v][adj[u][i].id].w+=p;
                    return p;
                }else dep[v]=-1;
            }
        }
        return 0;
    }

    int dinic(int S,int T){
        int ans=0,flow;
        while(bfs(S,T)){
            while(flow=dfs(S,INF,T)) ans+=flow;
        }
        return ans;
    }
}using namespace Dinic;

void init(){
    dtot=S=0;
    for(int i=0;i<=mx;i++){
        b[i]=0;
    }
    mx=0;
    for(int i=0;i<=T;i++){
        adj[i].clear();
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mx=max(mx,a[i]);
        b[a[i]]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++){
            id[i][j]=++dtot;
        }
    }
    T=dtot+1;
    for(int i=1;i<=mx;i++){
        if(b[i]){
            for(int j=i+i;j<=mx;j+=i){
                if(b[j]){
                    int x=b[i],y=b[j];
                    add(id[x][0],id[y][2],1);
                    add(id[x][0],id[y][3],1);
                    add(id[x][1],id[y][3],1);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        add(S,id[i][0],1);
        add(S,id[i][1],1);
        add(id[i][2],T,1);
        add(id[i][3],T,1);
        add(id[i][0],id[i][3],1);
    }
    cout<<dinic(S,T)-n<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}