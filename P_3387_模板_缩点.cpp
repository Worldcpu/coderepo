#include<iostream>
#include<stack>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MN=1e4+15,ME=1e5+15;
int n,m,w[MN],sw[MN],dfn[MN],cnt,tot,color[MN],low[MN],in[MN],dp[MN];
vector<int> adj[ME],slt[ME];
stack<int> s;
bool vis[MN];
void tarjan(int u){
    low[u]=dfn[u]=++cnt;
    s.push(u);
    vis[u]=1;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if(vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        tot++;
        int pre;
        do{
            pre=s.top();
            s.pop();
            color[pre]=tot;
            sw[tot]+=w[pre];
            vis[pre]=0;
        }while(pre!=u);
    }
}
int toposort(){
    queue<int>q;
    for(int i=1;i<=tot;i++){
        if(in[i]==0){
            q.push(i);
            dp[i]=sw[i];
        }
    }
    while (!q.empty())
    {
        int f=q.front();
        q.pop();
        for(int i=0;i<slt[f].size();i++){
            in[slt[f][i]]--;
            dp[slt[f][i]]=max(dp[slt[f][i]],dp[f]+sw[slt[f][i]]);
            if(in[slt[f][i]]==0){
                q.push(slt[f][i]);
            }
        }
    }
    int ans=-1;
    for(int i=1;i<=tot;i++){
        ans=max(ans,dp[i]);
    }
    return ans;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<adj[i].size();j++){
            if(color[adj[i][j]]!=color[i]){
                slt[color[i]].push_back(color[adj[i][j]]);
                in[color[adj[i][j]]]++;
            }
        }
    }
    // for(int i=1;i<=tot;i++){
    //     cout<<i<<":";
    //     for(int j=0;j<adj[i].size();j++){
    //         cout<<adj[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout<<toposort();
    return 0;
}