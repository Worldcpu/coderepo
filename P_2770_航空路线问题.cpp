#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,ME=520,INF=0x3f3f3f3f;
struct Edge{
    int v,w,c,id;
};
unordered_map<string,int> mp;
int n,m,S=MN-3,T=MN-2,tot,cur[MN],dis[MN],mincst;
vector<Edge> adj[MN];
string s[ME];
bool vis[MN],flag;

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

void dfs1(int u) { // u是出点，如1+n
    cout << s[u - n] << '\n'; // 转换为入点的名称
    vis[u - n] = 1;
    // 处理原图的边（u → v的入点）
    for (auto &e : adj[u]) {
        if (e.v >= 1 && e.v <= n && e.w == 0) {
            // 找到对应的出点v+n
            int next_out = e.v + n;
            // 遍历入点e.v的内部边是否被使用
            for (auto &e_in : adj[e.v]) {
                if (e_in.v == next_out && e_in.w == 0) {
                    dfs1(next_out);
                    break;
                }
            }
            break;
        }
    }
}

void dfs2(int u) { // u是出点
    vis[u - n] = 1;
    for (auto &e : adj[u]) {
        if (e.v >= 1 && e.v <= n && e.w == 0 && !vis[e.v]) {
            int next_out = e.v + n;
            for (auto &e_in : adj[e.v]) {
                if (e_in.v == next_out && e_in.w == 0) {
                    dfs2(next_out);
                    break;
                }
            }
        }
    }
    cout << s[u - n] << '\n'; // 后序遍历
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        mp[s[i]]=i;
        if(i==1){
            add(S,i,INF,0);
            add(i,i+n,2,-1);
        }else if(i==n) {
            add(i+n,T,INF,0);
            add(i,i+n,2,-1);
        }else add(i,i+n,1,-1);
    }
    for(int i=1;i<=m;i++){
        string u,v;
        cin>>u>>v;
        if(mp[u]>mp[v]) swap(u,v);
        add(mp[u]+n,mp[v],1,0);
        // add(mp[v]+n,mp[u],1,0);
        flag|=(mp[u]==1&&mp[v]==n);
    }
    int mxflow=dinic();
    if(mxflow==2){
        cout<<-mincst-2<<'\n';
    }else if(mxflow==1&&flag){
        cout<<"2\n"<<s[1]<<"\n"<<s[n]<<"\n"<<s[1];
        return 0;
    }else{
        cout<<"No Solution!";
        return 0;
    }
    memset(vis,0,sizeof(vis));
    dfs1(1+n);
    dfs2(1+n);
    return 0;
}