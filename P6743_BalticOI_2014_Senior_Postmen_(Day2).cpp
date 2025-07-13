#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,s[MN],a[MN],top,dcc,cnt;
bool vis[MN],svis[MN];
vector<pir> adj[MN];

void dfs(int u){
    for(int i=a[u];i<adj[u].size();i++){
        int v=adj[u][i].first,cnt=adj[u][i].second;
        a[u]++;
        if(!vis[cnt]){
            if(cnt&1){
                vis[cnt]=vis[cnt+1]=1;
            }else vis[cnt]=vis[cnt-1]=1;
            dfs(v);
        }
    }
    if(svis[u]){
        while(s[top]!=u){
            svis[s[top]]=0;
            cout<<s[top--]<<" ";
        }
        cout<<s[top]<<'\n';
    }else{
        svis[u]=1;
        s[++top]=u;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(pir(v,++cnt));
        adj[v].push_back(pir(u,++cnt));
    }
    dfs(1);
    return 0;
}
