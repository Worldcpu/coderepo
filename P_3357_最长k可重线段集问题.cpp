#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MK=520,INF=0x3f3f3f3f3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
struct Node{
    int l,r,d;
}line[MK];
int cur[MN],dis[MN],a[MN],b[MN],cnt,tot,mincst,n,K,S=MN-5,T=MN-4,S1=MN-3,T1=MN-2;
bool vis[MN];
vector<Edge> adj[MN];

int getdis(int x1,int y1,int x2,int y2){
    return (int)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

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
    int ans=0,flow;
    while(spfa()){
        while(flow=dfs(S,INF)) ans+=flow;// 这里和最大流的dinic不太一样，注意一下。
    }
    return ans;
}

bool cmp(Node x,Node y){
    return x.l<y.l;
}

signed main(){
    cin>>n>>K;
    add(S,S1,K,0);
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        line[i].l=min(x1,x2);
        line[i].r=max(x1,x2);
        line[i].d=getdis(x1,y1,x2,y2);
        //cout<<line[i].l<<" "<<line[i].r<<" "<<line[i].d<<'\n';
    }
    sort(line+1,line+1+n,cmp);
    for(int i=1;i<=n;i++){
        add(S1,i,1,0);
        add(i,i+n,1,-line[i].d);
        add(i+n,T,1,0);
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(line[i].l==line[i].r&&line[j].l==line[j].r&&line[i].l==line[j].l){
                continue;
            }
            if(line[j].l>=line[i].r||line[i].l>=line[j].r){
                add(i+n,j,INF,0);
            }
        }
    }
    dinic();
    cout<<-mincst;
    return 0;
}