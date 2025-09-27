#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int n,x[MN],y[MN],w[MN],id[MN],sumw;

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

int getdis(int a,int b){
    return abs(x[a]-x[b])+abs(y[a]-y[b]);
}

signed main(){
    S=MN-3,T=MN-2;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i]>>w[i];
        sumw+=w[i];
        add(i,i+n,w[i]);
        id[i]=((x[i]%2+2)%2)+2*((y[i]%2+2)%2);
        if(id[i]==3){
            add(S,i,INF);
        }else if(id[i]==1){
            add(i+n,T,INF);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(getdis(i,j)<=1){
                if((id[i]==0&&id[j]==1) || (id[i]==2&&id[j]==0) || (id[i]==3&&id[j]==2)){
                    add(i+n,j,INF);
                }
            }
        }
    }
    cout<<sumw-dinic(S,T);
    return 0;
}