#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MK=2e3+15,INF=0x3f3f3f3f3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
int N,p,m,f,n,s,S=MN-3,T=MN-2,cur[MN],dis[MN],mincst;
bool vis[MN];
vector<Edge> adj[MN];

void add(int u,int v,int w,int c){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,c,vs});
    adj[v].push_back({u,0,-c,us});
}

bool spfa(){// SPFA,有后遗症的自行替换
    queue<int> q;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
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
                    q.push(e.v);
                    vis[e.v]=1;
                }
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dis[T]!=INF);
}

int dfs(int u,int lim){
    if(u==T) return lim;
    vis[u]=1;
    int ret=0;
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;// 弧优化
        int v=adj[u][i].v;
        if(!vis[v]&&adj[u][i].w&&dis[v]==dis[u]+adj[u][i].c){
            int p=dfs(v,min(lim,adj[u][i].w));
            if(!p) dis[v]=INF;
            adj[u][i].w-=p;
            adj[v][adj[u][i].id].w+=p;
            ret+=p;
            lim-=p;
            mincst+=p*adj[u][i].c;// mincst在这里计算
            if(!lim) break;// 若流量为0则优化
        }
    }
    vis[u]=0;
    return ret;
}

int dinic(){
    int ans=0;
    while(spfa()){
        ans+=dfs(S,INF);// 这里和最大流的dinic不太一样，注意一下。
    }
    return ans;
}

// 主函数中输入参数部分
signed main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int awa;
        cin >> awa;
        add(S, i, awa, 0);  // 起点到脏餐巾节点
        add(i + N, T, awa, 0);  // 干净餐巾节点到汇点
    }
    int buy_price, fast_days, fast_cost, slow_days, slow_cost;
    cin >> buy_price >> fast_days >> fast_cost >> slow_days >> slow_cost;
    
    for (int i = 1; i <= N; i++) {
        if (i + 1 <= N) add(i, i + 1, INF, 0);  // 脏餐巾留到第二天
        if (i + fast_days <= N) add(i, i + N + fast_days, INF, fast_cost);  // 快洗
        if (i + slow_days <= N) add(i, i + N + slow_days, INF, slow_cost);  // 慢洗
        add(S, i + N, INF, buy_price);  // 购买餐巾
    }
    dinic();
    cout << mincst;
    return 0;
}