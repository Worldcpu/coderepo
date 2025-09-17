#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=65,MOD=1e9+7;
int n,m,K,ans,c[MN],d[MN],path[MN];
vector<int> adj[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

namespace DSU{
    int pre[MN],pst[MN];

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    void merge(int fr,int to){
        int rx=root(fr),ry=root(to);
        if(rx==ry) return;
        pre[rx]=ry;
        pst[ry]|=pst[rx];
    }

    void initpre(){
        for(int i=0;i<m;i++) pre[i]=i,pst[i]=path[i];
    }
} using namespace DSU;

namespace Tree{
    int dep[MN],fa[MN];

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
        }
    }

    int getst(int x,int y){
        if(x==y) return 1ll<<(x-1);
        int ret=0;
        if(dep[x]<dep[y]) swap(x,y);
        for(;dep[x]>dep[y];x=fa[x]) ret|=(1ll<<(x-1));
        for(;x!=y;x=fa[x],y=fa[y]) ret|=(1ll<<(x-1))|(1ll<<(y-1));
        return ret;
    }

} using namespace Tree;


int solve(int stt){
    initpre();
    for(int i=0;i<m;i++){
        if(!((stt>>i)&1)) continue;
        for(int j=i+1;j<m;j++){
            if(!((stt>>j)&1)) continue;
            if(path[i]&path[j]) merge(j,i);
        }
    }
    int cnt1=n-1,cnt2=0;
    for(int i=0;i<m;i++){
        if(!((stt>>i)&1)) continue;
        if(pre[i]==i){
            cnt1-=__builtin_popcountll(pst[i]);
            cnt2++;
        }
    }
    return ksm(K,cnt1+cnt2);
}

signed main(){
    freopen("pearl.in","r",stdin);
    freopen("pearl.out","w",stdout);
    cin>>n>>m>>K;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        path[i]=getst(x,y);
    }
    for(int s=0;s<(1ll<<m);s++){
        int cnt=__builtin_popcountll(s);
        if(cnt&1) ans=(ans-solve(s)+MOD)%MOD;
        else ans=(ans+solve(s))%MOD; 
    }
    cout<<ans<<"\n";
    return 0;
}
