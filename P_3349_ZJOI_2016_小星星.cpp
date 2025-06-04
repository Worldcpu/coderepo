#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=18;
int n,m,f[MN][MN],ans;
vector<int> adj[MN],lst;
bool mp[MN][MN];

void init(){
    memset(f,0,sizeof(f));
    lst.clear();
}

void dfs(int u,int pre){
    for(auto p:lst) f[u][p]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
    }
    for(auto p:lst){
        for(auto v:adj[u]){
            if(v==pre) continue;
            int sum=0;
            for(auto q:lst){
                if(!mp[p][q]) continue;
                sum+=f[v][q];
            }
            f[u][p]*=sum;
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        mp[u][v]=mp[v][u]=1;
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=0;i<(1<<n);i++){
        init();
        for(int j=1;j<=n;j++){
            if(!((i>>(j-1))&1)) lst.push_back(j);
        }
        dfs(1,0);
        int sum=0;
        for(auto p:lst) sum+=f[1][p]; 
        ans+=sum*(((__builtin_popcount(i))&1)?-1:1);
    }
    cout<<ans;
    return 0;
}
