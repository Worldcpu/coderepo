#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int v,vis,rev;
};
int n,s,t,top,cur[MN],st[MN],dg[MN];
bool vis[MN];
vector<vector<int>> a;
vector<Edge> adj[MN];

void add(int u,int v){
    int sizu=adj[u].size(),sizv=adj[v].size();
    adj[u].push_back((Edge){v,0,sizv});
    adj[v].push_back((Edge){u,0,sizu});
}

void dfs(int u){
    vis[u]=1;
    for(int i=cur[u];i<adj[u].size();i=max(i+1,cur[u])){
        auto &now=adj[u][i];
        if(!now.vis){
            now.vis=1;
            adj[now.v][now.rev].vis=1;
            cur[u]=i+1;
            dfs(now.v);
        }
    }
    st[++top]=u;
}

void solve(int l,int r){
    int len=r-l+1,dtot=t;
    unordered_map<int,pir> pos;
    for(int i=0;i<len/2;i++){
        for(int j=1;j<=n;j++){
            int u=a[j][l+i],v=a[j][r-i];
            if(u==v) continue;
            add(u,++dtot);
            add(v,dtot);
            pos[dtot]=pir(i,j);
            dg[u]++;
            dg[v]++;
            dg[dtot]+=2;
        }
    }
    for(int i=1;i<=t;i++){
        if(dg[i]&1){
            add(0,++dtot);
            add(dtot,i);
        }
    }
    for(int i=0;i<=t;i++){
        if(!vis[i]){
            top=0;
            dfs(i);
            reverse(st+1,st+1+top);
            for(int j=3;j<=top;j+=2){
                if(!st[j]||!st[j-2]||st[j]==st[j-2]) continue;
                int d=st[j-1];
                auto [pi,pj]=pos[d];
                if(a[pj][l+pi]!=st[j-2]){
                    swap(a[pj][l+pi],a[pj][r-pi]);
                }
            }
        }
    }
    for(int i=0;i<=dtot+t;i++){
        adj[i].clear();
        vis[i]=0;
        dg[i]=cur[i]=0;
    }
    if(len!=2){
        int mid=(l+r)>>1;
        solve(l,mid);
        solve(mid+1,r);
    }
}

int main(){
    cin>>n>>s>>t;
    a.resize(n+1);
    for(int i=1;i<=n;i++){
        a[i].resize(s+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=s;j++){
            cin>>a[i][j];
        }
    }
    solve(1,s);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=s;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<'\n';
    }

    return 0;
}