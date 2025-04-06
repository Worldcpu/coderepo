#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=1e4+15,INF=1e9;
struct edge{
    int v,len,id;
};
vector<edge> adj[MN];
int n,m,s=0,t=1e4,tot,cnt;
int flow[MN],cur[MN],dep[MN];

void add(int u,int v,int flw){
    int szu=adj[u].size(),szv=adj[v].size();
    adj[u].push_back({v,flw,szv});
    adj[v].push_back({u,0,szu});
}

bool bfs(){
    memset(dep,-1,sizeof(dep));
    queue<int> q;
    q.push(s);
    dep[s]=0;
    while (!q.empty())
    {
        int u=q.front();
        q.pop();
        for(auto e:adj[u]){
            int v=e.v,len=e.len;
            if(dep[v]==-1&&len){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return (dep[t]!=-1);
}

int dfs(int u,int limit){
    if(u==t) return limit;
    int fl=0;
    for(int &i=cur[u];i<adj[u].size();i++){
        int v=adj[u][i].v;
        if(dep[v]==dep[u]+1&&(adj[u][i].len)){
            int p=dfs(v,min(adj[u][i].len,limit));
            if(p){
                adj[u][i].len-=p;
                adj[v][adj[u][i].id].len +=p;
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

int head[MN];

void solve(){
    // 常规思想最慢解，时间复杂度O(n^4)
    // 显然可以模拟，显然可以二分图
    s=0;
    t=1e4;
    tot=0;
    cnt=0;
    cin>>n;
    for(int i=0;i<=2*n*n;i++){
        adj[i].clear();
        flow[i]=cur[i]=dep[i]=0;
    }
    while (tot<=n)
    {
        cnt++;
        add(s,cnt<<1,1);
        add(cnt<<1|1,t,1);
        for(int i=sqrt(cnt)+1;i*i<(cnt<<1);i++){
            add((i*i-cnt)<<1,cnt<<1|1,1);
        } 
        int mxflow=dinic();
        if(!mxflow){
            head[++tot]=cnt;
        }
    }
    cout<<cnt-1<<'\n';//汇点减去
}

int main(){
    int T;
    cin>>T;
    while (T--)
    {
        solve();
    }
    
    return 0;
}