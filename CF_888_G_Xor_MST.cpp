#include<bits/stdc++.h>
#define int long lon
using namespace std;
constexpr int MN=1e7+15,INF=1e18;
int n,ans,a[MN];

struct Trie{
    int nxt[MN][2],tot;

    void insert(int x){
        int p=0;
        for(int i=30;i>=0;i--){
            int k=(x>>i)&1;
            if(!nxt[p][k]) nxt[p][k]=++tot;
            p=nxt[p][k];
        }
    }

    int query(int x,int y,int dp){
        if(dp<0) return 0;
        int ret=INF;
        for(int i=0;i<2;i++){
            if(nxt[x][i]&&nxt[y][i]) ret=min(ret,query(nxt[x][i],nxt[y][i],dp-1));
        }
        if(ret!=INF) return ret;
        for(int i=0;i<2;i++){
            if(nxt[x][i]&&nxt[y][!i]) ret=min(ret,query(nxt[x][i],nxt[y][!i],dp-1)+(1<<dp));
        }
        return ret;
    }

    void dfs(int u,int dp){
        if(dp<0) return;
        if(nxt[u][0]&&nxt[u][1]) ans+=query(nxt[u][0],nxt[u][1],dp-1)+(1<<dp);
        if(nxt[u][0]) dfs(nxt[u][0],dp-1);
        if(nxt[u][1]) dfs(nxt[u][1],dp-1);
    }

}t;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    n=unique(a+1,a+1+n)-a-1;
    for(int i=1;i<=n;i++){
        t.insert(a[i]);
    }
    t.dfs(0,30);
    cout<<ans;
    return 0;
}