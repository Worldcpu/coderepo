#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int MN=1e6+15;
const ull P=114514191981019;
random_device rd;
mt19937 mt;
set<ull> s;
int n,m;
ull f[MN],g[MN],xorp;
vector<int> adj[MN];
map<int,int> mp;

ull xorshift(ull x){
    x^=xorp;
    x^=(x<<13);
    x^=(x>>17);
    x^=(x<<5);
    return x+P;
}

void dfs1(int u,int fa){
    f[u]=0;
    for(auto v:adj[u]){
        if(v==fa) continue;
        dfs1(v,u);
        f[u]+=xorshift(f[v]);
    }
    f[u]+=xorp;
    s.insert(f[u]);
}

void dfs2(int u,int fa){
    for(auto v:adj[u]){
        if(v==fa) continue;
        g[v]=f[v]+xorshift(g[u]-xorshift(f[v]));
        dfs2(v,u);
    }
}

int main(){
    mt.seed(rd());
    xorp=mt();
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>n;
        for(int i=1;i<=n;i++){
            adj[i].clear();
            f[i]=g[i]=0;
        }
        for(int i=1;i<=n;i++){
            int fa;
            cin>>fa;
            if(fa==0) continue;
            adj[fa].push_back(i);
            adj[i].push_back(fa);
        }
        dfs1(1,0);
        g[1]=f[1];
        dfs2(1,0);
        ull maxx=INT64_MIN;
        for(int i=1;i<=n;i++){
            maxx=max(maxx,g[i]);
        }
        if(mp[maxx]){
            cout<<mp[maxx]<<'\n';
        }else{
            cout<<i<<'\n';
            mp[maxx]=i;
        }
    }
    return 0;
}