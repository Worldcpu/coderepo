#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int MN=1e4+15,INF=1e9;
int n,m,rt,q[MN];
// siz表示子树大小，maxp表示删除结点u后产生的子树中最大的那棵大小
int siz[MN],maxp[MN];

// sum即总节点个数 s即存储judge标记过的节点
// 每一次暴力memset时间复杂度超高
int sum,s[MN];

// query即询问结果，dis即距离
// judge[dis]表示在子树中是否存在某个节点到rt举例为dis
// rem即子树中每个节点到rt的距离
bool judge[MN],query[MN];
int rem[MN],dis[MN];

struct edge
{
    int v,w;
};

vector<edge> adj[MN];
bool vis[MN];

// 求重心
void dfs(int u,int fa){
    siz[u]=1;
    maxp[u]=0;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa||vis[v]) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        maxp[u]=max(maxp[u],siz[v]);
    }
    maxp[u]=max(maxp[u],sum-siz[u]);
    if(maxp[u]<maxp[rt])rt=u;
}

// 获取距离
void getdis(int u,int fa){
    rem[++rem[0]]=dis[u];
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa||vis[v]) continue;
        dis[v]=dis[u]+w;
        getdis(v,u);
    }
}

void clac(int u){
    int p=0;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]) continue;
        rem[0]=0;
        dis[v]=w;
        getdis(v,u);//求当前子树的各点距离
        for(int i=rem[0];i;i--){//遍历当前子树的dis，考虑子树内点配对
            for(int j=1;j<=m;j++){
                if(q[j]>=rem[i]){
                    query[j]|=judge[q[j]-rem[i]];//如果有配对的就更新询问结果
                }
            }
        }
        for(int i=rem[0];i;i--){
            s[++p]=rem[i];
            judge[rem[i]]=1;
            //保存出现过的dis于judge
        }
    }
    for(int i=1;i<=p;i++){
        judge[s[i]]=0;// 清空judge
    }
}

void solve(int u){
    vis[u]=judge[0]=1;
    clac(u);//计算当前为根的子树答案贡献
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(vis[v]) continue;
        //重新设置，再次求重心再跑solve
        sum=siz[v];
        rt=0;
        maxp[rt]=INF;
        dfs(v,0);
        solve(rt);
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    for(int i=1;i<=m;i++){
        cin>>q[i];//离线询问
    }

    maxp[rt]=sum=n;
    dfs(1,0);
    solve(rt);

    for(int i=1;i<=m;i++){
        if(query[i]) cout<<"AYE\n";
        else cout<<"NAY\n";
    }
    return 0;
}