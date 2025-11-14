#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=1e9+7;
int n,ans,dg[MN],st[MN];
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

namespace Tree{
    int dfn[MN],fa[MN],dtot,siz[MN];

    void dfs1(int u,int pre){
        dfn[u]=++dtot;
        siz[u]=1;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
        }
    }

    // x 是否是 y 祖先
    bool isanc(int x,int y){
        return dfn[y]>=dfn[x]&&dfn[y]<=dfn[x]+siz[x]-1;
    }

}using namespace Tree;

int sol(int x,int y){
    // a[x]=1 a[y]=2;
    int nowx=fa[x],nowy=fa[y],cnt=n-2;
    while(1){
        if(nowx==nowy){
            return ksm(2,cnt);
        }
        if(isanc(nowy,nowx)){
            return ksm(2,cnt-1);         
        }else if(isanc(nowx,nowy)) return ksm(2,cnt);
        nowx=fa[nowx],nowy=fa[nowy];
        cnt-=2;
    }
}

void init(){
    st[0]=0;
    dtot=0;
    for(int i=1;i<=n;i++){
        dg[i]=0;
        adj[i].clear();
        dfn[i]=siz[i]=fa[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        dg[u]++;
        dg[v]++;
    }
    dfs1(1,0);
    for(int i=2;i<=n;i++){
        if(dg[i]==1){
            st[++st[0]]=i;
        }
    }
    if(st[0]>2){
        cout<<0<<'\n';
        return;
    }
    if(st[0]==1){
        cout<<ksm(2,n)<<'\n';
        return;
    }
    cout<<(sol(st[1],st[2])+sol(st[2],st[1]))%MOD<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}