#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,MK=520,INF=0x3f3f3f3f;
struct Edge{
    int v,w,c,id;
};

int L[MK],R[MK],id[MK],cur[MN],dis[MN],a[MN],b[MN],cnt,tot,mincst,n,K,S=MN-3,T=MN-2;
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
void lisan(){
    sort(a+1,a+1+tot);
    for(int i=1;i<=tot;i++){
        if(i==1||(a[i]!=a[i-1])) b[++cnt]=a[i];
    }
    for(int i=1;i<=n;i++){
        L[i]=lower_bound(b+1,b+1+cnt,L[i])-b;
        R[i]=lower_bound(b+1,b+1+cnt,R[i])-b;
    }
}

int main(){
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        a[++tot]=L[i];
        a[++tot]=R[i];
    }
    lisan();
    // for(int i=1;i<=n;i++){
    //     cout<<L[i]<<" "<<R[i]<<'\n';
    // }
    // cout<<"CNT:"<<cnt<<'\n';
    for(int i=1;i<=cnt;i++){
        if(i==1) add(S,i,K,0);
        else if(i==cnt) add(i,T,K,0),add(i-1,i,K,0);
        else add(i-1,i,K,0);
    }
    for(int i=1;i<=n;i++){
        add(L[i],R[i],1,-(b[R[i]]-b[L[i]]));
    }
    dinic();
    cout<<-mincst;
    return 0;
}