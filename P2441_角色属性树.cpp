#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int fa[MN],n,a[MN],m;
vector<int> adj[MN];

void dfs1(int u,int pre){
    fa[u]=pre;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
    }
}

int dfs2(int u,int st){
    if(!u) return -1; 
    if(__gcd(a[u],a[st])>1) return u;
    return dfs2(fa[u],st);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    while(m--){
        int op,x,y;
        cin>>op>>x;
        if(op==1){
            cout<<dfs2(fa[x],x)<<'\n';
        }
        else{
            cin>>y;
            a[x]=y;
        }
    }
    return 0;
}
