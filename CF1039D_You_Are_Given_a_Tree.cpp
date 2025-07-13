#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,bl,fa[MN],ans[MN],f[MN],dfn[MN],dtot;
vector<int> adj[MN];

void dfs(int u,int pre){
    fa[u]=pre;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
    }
    dfn[++dtot]=u;
}

int solve(int k){
    int ret=0;
    for(int i=1;i<=n;i++) f[i]=1;
    for(int i=1;i<=n;i++){
        int u=dfn[i],pre=fa[u];
        if(pre&&f[u]!=-1&&f[pre]!=-1){
            if(f[u]+f[pre]>=k){
                ret++;
                f[pre]=-1;
            }else f[pre]=max(f[pre],f[u]+1);
        }
    }
    return ret;
}

int main(){
    cin>>n;
    bl=sqrt(n*__lg(n));
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    ans[1]=n;
    for(int i=2;i<=bl;i++){
        ans[i]=solve(i);
    }
    for(int i=bl+1;i<=n;i++){
        int tmp=solve(i);
        int l=i,r=n,cnt=i;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(solve(mid)==tmp){
                cnt=max(cnt,mid);
                l=mid;
            }else r=mid;
        }
        for(;i<=cnt;i++) ans[i]=tmp;
        i--;
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
    return 0;
}
