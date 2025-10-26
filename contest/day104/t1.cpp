#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=2e6+15;
constexpr ull base=1145141919810;
struct Edge{
    int v;
    ull w;
};
int n,dg[MN],d[MN][4],ans[MN],res;
bool vis[MN];
vector<Edge> adj[MN];
unordered_map<int,int> mp[MN];
unordered_map<ull,int> visw;

void dfs(int u){
    vis[u]=1;
    for(auto e:adj[u]){
        if(!visw[e.w]){
            res++;
            visw[e.w]=1;
        }
        if(vis[e.v]){
            ans[u]=res;
            return;
        }
        dfs(e.v);
    }
    ans[u]=res;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>dg[i];
        for(int j=0;j<dg[i];j++){
            cin>>d[i][j];
            mp[i][d[i][j]]=j;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<dg[i];j++){
            int v=d[i][j],pos=j-1;
            if(j==0) pos=dg[i]-1; 
            ull w=max(i,v)*base+min(i,v);
            adj[n*pos+i].push_back({n*mp[v][i]+v,w});
        }
    }
    for(int i=1;i<=n;i++){
        int u=(dg[i]-1)*n+i;
        if(!vis[u]){
            res=0;
            visw.clear();
            dfs(u);
        }
        cout<<ans[u]<<'\n';
    }
    return 0;
}