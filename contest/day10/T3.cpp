#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,ans,dg[MN],pos[MN],cntc[MN];
vector<int> G[MN],adj[MN];



signed main(){
    freopen("cycle.in","r",stdin);
    freopen("cycle.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
        dg[u]++,dg[v]++;
    }
    for(int i=1;i<=n;i++){
        for(auto v:G[i]){
            if(dg[i]>dg[v]||(dg[i]==dg[v]&&i>v)){
                adj[i].push_back(v);
            }
        }
    }
    for(int a=1;a<=n;a++){
        for(auto b:adj[a]){
            for(auto c:G[b]){
                if(dg[c]>dg[a]||(dg[c]==dg[a]&&c>=a)) continue;
                ans+=cntc[c];
                cntc[c]++;
            }
        }
        for(auto b:adj[a]){
            for(auto c:G[b]){
                cntc[c]=0;
            }
        }
    }
    cout<<ans;

    return 0;
}