#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5520+15;
int A,B,m,a[MN],b[MN],tim,ans;
vector<int> adj[MN],e[MN];
map<pir,bool> ump;

namespace Hungry{
    int mat[MN],vis[MN],mark[MN];

    bool match(int u,int tim,int tgt){
        if(vis[u]==tim) return 0;
        vis[u]=tim;
        for(auto v:adj[u]){
            if(mark[v]!=tgt) continue;
            if(vis[v]!=tim){
                vis[v]=tim;
                if(!mat[v]||match(v,tim,tgt)){
                    mat[v]=u;
                    return 1;
                }
            }
        }
        return 0;
    }
}using namespace Hungry;

void init(){
    for(int i=1;i<=B;i++){
        adj[i].clear();
    }
    for(int i=1;i<=A;i++) e[i].clear();
    memset(mark,0,sizeof(mark));
    ans=tim=0;
}

void solve(){
    cin>>A>>B>>m;
    init();
    for(int i=1;i<=A;i++){
        cin>>a[i];
    }
    for(int i=1;i<=B;i++){
        cin>>b[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
    }
    for(int i=1;i<=B;i++){
        if(!(b[i]&1)) continue;
        for(int j=1;j<=B;j++){
            if((b[j])&1) continue;
            int v=(b[i]|b[j]);
            if(!(__builtin_popcount(v)&1)){
                adj[i].push_back(j);
            }
        }
    }
    for(int i=1;i<=B;i++){
        if(b[i]&1){
            ans+=match(i,++tim,0);
        }
    }
    ans=B-ans;
    for(int i=1;i<=A;i++){
        memset(vis,0,sizeof(vis));
        memset(mat,0,sizeof(mat));
        for(auto v:e[i]){
            mark[v]=i;
        }
        tim=0;
        int ret=0;
        for(auto v:e[i]){
            if(b[v]&1){
                ret+=match(v,++tim,i);
            }
        }
        int qwq=e[i].size()-ret+1;
        ans=max(ans,qwq);
    }
    for(int i=1;i<=A;i++){
        for(int j=i+1;j<=A;j++){
            if(!((a[i]&1)^(a[j]&1))) continue;
            int tot=0;
            ump.clear();
            for(auto v:e[i]){
                ump[pir(i,v)]=1;
            }
            for(auto v:e[j]){
                if(ump[pir(i,v)]){
                    mark[v]=i*A+j;
                    ++tot;
                }
            }
            memset(vis,0,sizeof(vis));
            memset(mat,0,sizeof(mat));
            tim=0;
            int ret=0;
            for(auto v:e[i]){
                if((b[v]&1)&&mark[v]==i*A+j){
                    ret+=match(v,++tim,i*A+j);
                }
            }
            int qwq=tot-ret+2;
            ans=max(ans,qwq);
        }
    }
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