#include<bits/stdc++.h>
#define ll long long
#define pir pair<int,int>
using namespace std;
const int MN=1e6+15;
struct circle
{
    int u,v;
};

struct edge{
    int v,id;
};
int n,pre[MN];
ll val[MN],f[MN][2];
vector<edge> adj[MN];
vector<pir> cir;

int root(int x){
    if(x==pre[x]) return x;
    else return pre[x]=root(pre[x]);
}

void init(){
    for(int i=1;i<=n;i++){
        pre[i]=i;
    }
}

void dfs(int u,int fa){
    f[u][0]=0;
    f[u][1]=val[u];
    for(auto e:adj[u]){
        int v=e.v,id=e.id;
        if(v==fa) continue;
        dfs(v,u);
        f[u][1]+=f[v][0];
        f[u][0]+=max(f[v][0],f[v][1]);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        int v;
        cin>>val[i]>>v;
        int ri=root(i),rv=root(v);
        if(ri==rv){
            cir.push_back(pir(i,v));
            continue;
        }else pre[rv]=ri;
        adj[i].push_back({v,i});
        adj[v].push_back({i,i});
    }
    ll ans=0;
    for(auto awa:cir){
        dfs(awa.first,0);
        ll ret=f[awa.first][0];
        dfs(awa.second,0);
        ans+=max(ret,f[awa.second][0]);
    }
    cout<<ans;
    return 0;
}