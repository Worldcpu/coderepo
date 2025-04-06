#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15,INF=1e9;
int n,m,s,t,cur[MN],to[MN],dep[MN];
bool vis[MN];
struct edge
{
    int v,len,id;
};
vector<edge> adj[MN];
void add(int u,int v,int c){
    int uz=adj[u].size();
    int vz=adj[v].size();
    adj[u].push_back({v,c,vz});
    adj[v].push_back({u,0,uz});
}
bool bfs(){
    memset(dep,-1,sizeof(dep));
    queue<int> q;
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
    if(u==t) return limit;
    int flow=0;
    for(int &i=cur[u];i<adj[u].size();i++){
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&adj[u][i].len){
            int p=dfs(v,min(adj[u][i].len,limit));
            if(p){
                to[u]=v;
                if(v!=t&&to[u]>n){
                    vis[v-n]=1;
                }
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
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int now=i;
            cout<<now<<" ";
            while (to[now]&&to[now]!=t)
            {
                cout<<to[now]-n<<" ";
                now=to[now]-n;
            }
            cout<<"\n";
        }
    }
    // cout<<"MAMBAOUT"<<endl;
    return ans;
}
int main(){
    // freopen("ans.in","r",stdin);
    cin>>n>>m;
    s=0;
    t=2*n+1;
    for(int i=1;i<=n;i++){
        add(s,i,1);
        add(i+n,t,1);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        add(u,v+n,1);
    }
    int anss=dinic();
    // cout<<n-anss;
    cout<<n-anss;
    return 0;
}