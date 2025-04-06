#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
const int MN=3e5+15,ML=25;
int dep[MN],fa[MN][40],a[MN],n,sum[MN];
vector<int> adj[MN];
void dfs(int u,int pre){
    fa[u][0]=pre;
    dep[u]=dep[pre]+1;
    for(int i=1;i<=ML;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(auto v:adj[u]){
        if(v!=pre){
            dfs(v,u);
        }
    }
}
int lca(int x,int y){
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    for(int i=ML;i>=0;i--){
        if(dep[fa[y][i]]>=dep[x]){
            y=fa[y][i];
        }
    }
    if(x==y) return x;
    for(int i=ML;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
void dfss(int u,int pre){
    for(auto v:adj[u]){
        if(v!=pre){
            dfss(v,u);
            sum[u]+=sum[v];
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<n;i++){
        int l=a[i],r=a[i+1];
        int lc=lca(l,r);
        sum[l]++;
        sum[r]++;
        sum[lc]--;
        if(lc!=1)sum[fa[lc][0]]--;
    }
    // cout<<"AWA";
    dfss(1,0);
    for(int i=2;i<=n;i++){
        sum[a[i]]--;
    }
    for(int i=1;i<=n;i++){
        cout<<sum[i]<<endl;
    }
    return 0;
}