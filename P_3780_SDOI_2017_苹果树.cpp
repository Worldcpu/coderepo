#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e4+15,MV=2e7+15;
int n,m,K,ans,fa[MN],a[MN],b[MN],f[MV],g[MV],q1[MN];
vector<int> adj[MN];

namespace Tree{
    
    void solve(int *f,int A,int B){
        static int p[MN]={},q[MN]={};
	    int ql=1,qr=0;
	    for(int i=0,j=0;i<=m;i++,j+=B){
		    while(ql<=qr && p[qr]<=f[i]-j) qr--;
		    p[++qr]=f[i]-j;
            q[qr]=i;
		    while(ql<=qr && q[ql]<i-A) ql++;
		    f[i]=p[ql]+j;
	    }
    }

    void dfs1(int u){
        if(a[u]) solve(f+u*K,a[u],b[u]);
        for(auto v:adj[u]){
            memcpy(f+v*K,f+u*K,K*sizeof(int));
            dfs1(v);
            int *s=f+u*K+1,*e=f+v*K;
            for(int i=1;i<=m;i++,s++,e++){
                *s=max(*s,*e+b[v]);
            }
        }
    }

    void dfs2(int u,int x){
        x+=b[u];
        for(auto v:adj[u]){
            memcpy(g+v*K,g+u*K,K*sizeof(int));
            dfs2(v,x);
            int *s=g+u*K+1,*e=g+v*K;
            for(int i=1;i<=m;i++,s++,e++){
                *s=max(*s,*e+b[v]);
            }
        }
        if(adj[u].empty()){
            int *s=f+u*K+m,*e=g+u*K;
            for(int i=0;i<=m;i++,s--,e++){
                ans=max(ans,*s+*e+x);
            }
        }
        if(a[u]) solve(g+u*K,a[u],b[u]);
    }
}using namespace Tree;

void init(){
    ans=0;
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++){
        adj[i].clear();
    }
}

void solve(){
    cin>>n>>m;
    K=m+1;
    init();
    for(int i=1;i<=n;i++){
        cin>>fa[i]>>a[i]>>b[i];
        --a[i];
        if(i>1) adj[fa[i]].push_back(i);
    }
    dfs1(1);
    for(int i=1;i<=n;i++) adj[i].clear();
    for(int i=n;i>=1;i--) adj[fa[i]].push_back(i);
    dfs2(1,0);
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }


    return 0;
}