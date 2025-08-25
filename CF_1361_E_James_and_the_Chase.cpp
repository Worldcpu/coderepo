#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,rt,ans;
vector<int> adj[MN];
multiset<int> s[MN];
mt19937 mt;

namespace Tree{
    int fa[MN],in[MN],out[MN],up[MN],dtot;
    bool isok[MN];

    void dfs1(int u){
        in[u]=++dtot;
        for(auto v:adj[u]){
            if(in[v]) continue;
            fa[v]=u;
            dfs1(v);
        }
        out[u]=dtot;
    }

    void dfs2(int u){
        for(auto v:adj[u]){
            if(in[v]<=in[u]){
                s[u].insert(v);
            }else{
                dfs2(v);
                if(s[u].size()<s[v].size()) swap(s[u],s[v]);
                for(auto p:s[v]) s[u].insert(p);
            }
        }
        s[u].erase(u);
        if(s[u].size()==1){
            up[u]=*s[u].begin();
        }
    }

    void dfs3(int u){
        isok[u]|=isok[up[u]];
        if(isok[u]) ans++;
        for(auto v:adj[u]){
            if(in[v]>in[u]) dfs3(v);
        }
    }

}using namespace Tree;

void initchk(){
    dtot=0;
    for(int i=1;i<=n;i++){
        fa[i]=up[i]=in[i]=out[i]=0;
    }
}

bool check(int u){
    initchk();
    dfs1(u);
    for(int i=1;i<=n;i++){
        for(auto v:adj[i]){
            if(fa[v]!=i){
                if(in[v]>in[i]||out[v]<out[i]) return 0;
            }
        }
    }
    return 1;
}

void init(){
    dtot=ans=rt=0;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        s[i].clear();
        isok[i]=0;
    }
}

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    for(int qwq=1;qwq<=100;qwq++){
        int u=getrd(1,n);
        if(check(u)){
            rt=u;
            break;
        }
    }
    if(!rt){
        cout<<-1<<'\n';
        return;
    }
    dfs2(rt);
    isok[rt]=1;
    dfs3(rt);
    if(ans*5<n){
        cout<<-1<<'\n';
        return;
    }
    for(int i=1;i<=n;i++){
        if(isok[i]) cout<<i<<' ';
    }
    cout<<'\n';
}

int main(){
    mt.seed(time(0));
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}