#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=1e9+7;
int n,q,t,a[MN],f[MN],in[MN],dtot,ch;
bool vis[MN];

namespace Tree{
    int nxt[MN],fa[MN],suf[MN];
    vector<int> vct[MN];

    void dfs1(int u,int sum){
        if(!u) return;
        vct[dtot].push_back(u);
        vis[u]=1;
        dfs1(nxt[u],sum+a[nxt[u]]);
    }
}using namespace Tree;

namespace DP{
    int w[MN],wtot,f[MN];

    int solve(){
        if(t<0){
            return 0;
        }
        f[0]=1;
        for(int i=1;i<=wtot;i++){
            for(int j=w[i];j<=t;j++){
                f[j]=(f[j]+f[j-w[i]])%MOD;
            }
        }
        return f[t];
    }
}


signed main(){
    cin>>n>>q>>t;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=q;i++){
        int u,v;
        cin>>v>>u;
        nxt[u]=v;
        fa[v]=u;
    }

    for(int i=1;i<=n;i++){
        if(!vis[i]&&!fa[i]){
            dtot++;
            dfs1(i,a[i]);
        }
    }
    
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            cout<<0<<'\n';
            return 0;
        }
    }

    for(int i=1;i<=dtot;i++){
        int cnt=0;
        for(auto p:vct[i]){
            t-=a[p]*(cnt++);
        }       
    }
    for(int i=1;i<=dtot;i++){
        reverse(vct[i].begin(),vct[i].end());
        suf[vct[i][0]]=a[vct[i][0]];
        for(int j=1;j<vct[i].size();j++){
            suf[vct[i][j]]=a[vct[i][j]]+suf[vct[i][j-1]];
        }
        reverse(vct[i].begin(),vct[i].end());
        for(auto p:vct[i]){
            DP::w[++DP::wtot]=suf[p];
        }
    }
    cout<<DP::solve()<<'\n';
    return 0;
}