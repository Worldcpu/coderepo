#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int n,rt,tot,ra[MN],rb[MN];
bool vis[MN];

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
            for(auto &e:adj[u]){
                if(dep[e.v]==-1&&e.w>0){
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
        for(int &i=cur[u];i<(int)adj[u].size();i++){
            int v=adj[u][i].v;
            if(dep[v]==dep[u]+1 && adj[u][i].w>0){
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
            while( (flow=dfs(S,INF,T)) ){
                ans+=flow;
            }
        }
        return ans;
    }
}using namespace Dinic;

void dfs_rec(int u){
    for(auto &e:adj[u]){
        int v=e.v;
        int fv=v-n;
        if(v==S || vis[v]) continue;
        vis[v]=1;
        for(auto &fe:adj[v]){
            if(fe.w>0 && fe.v!=T){
                tot++;
                ra[fv]=u;
                rb[fv]=fe.v;
                dfs_rec(fe.v); // 注意递归的是左侧点
            }
        }
    }
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    S = 0;
    T = n<<1;


    for(int i=1;i<n;i++){
        int num;
        cin>>num;
        add(i+n,T,1);
        for(int j=1;j<=num;j++){
            int x;
            cin>>x;
            add(x,i+n,1);
        }   
    }
    for(int i=1;i<=n;i++){
        add(S,i,1);
    }
    int mxflow=dinic(S,T);
    if(mxflow<n-1){
        cout<<-1;
        return 0;
    }
    for(auto &e:adj[S]){
        int v=e.v,w=e.w;
        if(w){
            rt=v;
        }
    }
    dfs_rec(rt);
    if(tot!=n-1){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<n;i++){
        cout<<ra[i]<<' '<<rb[i]<<'\n';
    }
    return 0;
}
