#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=1e5+15,INF=1e9;
// sum就是题面意思的sum答案,summ即节点总数
// visc即表示这个颜色已经访问过了
// cnt即子树对当前节点的贡献,下表应为颜色。siz即子树大小
ll n,c[MN];
int vis[MN];
ll cnt[MN],siz[MN],sum,summ,ans[MN],visc[MN];

vector<int> adj[MN];
ll rt,maxp[MN];
void dfs(int u,int fa){
    siz[u]=1;
    maxp[u]=0;
    for(auto v:adj[u]){
        if(v==fa||vis[v]) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        maxp[u]=max(maxp[u],siz[v]);
    }
    maxp[u]=max(maxp[u],summ-siz[u]);
    if(maxp[u]<maxp[rt]){
        rt=u;
    }
}

void getdis(int u,int fa,int now){
    // now即当前路径（不含u）的颜色数
    siz[u]=1;
    if(!visc[c[u]]){
        sum-=cnt[c[u]];
        now++;
    }
    visc[c[u]]++;
    ans[u]+=sum+now*siz[rt];
    // 前面是其他颜色到当前节点的贡献
    // 后面是跨rt（就是跨子树,相当于rt就是路径拐点）的贡献
    for(auto v:adj[u]){
        if(v==fa||vis[v]) continue;
        getdis(v,u,now);
        siz[u]+=siz[v];
    }
    visc[c[u]]--;
    if(!visc[c[u]]){
        sum+=cnt[c[u]];// 回溯防止处理下一个子树出问题
    }
}

void getcnt(int u,int fa){
    if(!visc[c[u]]){
        // 统计答案
        cnt[c[u]]+=siz[u];
        sum+=siz[u];
    }
    visc[c[u]]++;
    for(auto v:adj[u]){
        if(v==fa||vis[v]) continue;
        getcnt(v,u);
    }
    visc[c[u]]--;
}

void clear(int u,int fa,int now){
    if(!visc[c[u]]){
        now++;
    }
    visc[c[u]]++;
    ans[u]-=now;
    ans[rt]+=now;
    for(auto v:adj[u]){
        if(v==fa||vis[v]) continue;
        clear(v,u,now);
    }
    visc[c[u]]--;
    cnt[c[u]]=0;
}

void clearcnt(int u,int fa){
    cnt[c[u]]=0;
    for(auto v:adj[u]){
        if(v==fa||vis[v]) continue;
        clearcnt(v,u);
    }
}

void solve(int u){
    vis[u]=1;
    ans[u]++;
    rt=u;
    siz[u]=sum=cnt[c[u]]=1;
    visc[c[u]]++;
    for(auto v:adj[u]){
        if(vis[v]) continue;
        getdis(v,u,0);
        getcnt(v,u);
        siz[u]+=siz[v];
        cnt[c[u]]+=siz[v];
        sum+=siz[v];
    }
    clearcnt(u,0);
    siz[u]=sum=cnt[c[u]]=1;
    for(int i=adj[u].size()-1;i>=0;i--){
        int v=adj[u][i];
        if(vis[v]) continue;
        getdis(v,u,0);
        getcnt(v,u);
        siz[u]+=siz[v];
        cnt[c[u]]+=siz[v];
        sum+=siz[v];
    }
    visc[c[u]]--;
    clear(u,0,0);
    for(auto v:adj[u]){
        if(vis[v]) continue;
        summ=siz[v];
        rt=0;
        maxp[rt]=INF;
        dfs(v,u);
        solve(rt);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    summ=n;
    maxp[rt]=n+1;
    dfs(1,0);
    solve(rt);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}