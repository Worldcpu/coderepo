#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15,MK=30;
int n,m,K;
int f[MN][MK];
string st;
vector<int> adj[MN];

void init(){
    for(int i=1;i<=n;i++){
        adj[i].clear();
        for(int j=1;j<=K;j++) f[i][j]=0;
    }
}

void solve(){
    cin>>n>>m>>K>>st;
    init();
    st=" "+st;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        f[i][K<<1]=st[i]=='A';
    }
    for(int k=(K<<1)-1;k>=0;k--){
        for(int u=1;u<=n;u++){
            if(k&1){
                int ret=1;
                for(auto v:adj[u]){
                    if(!f[v][k+1]){
                        ret=0;
                        break;
                    }
                }
                f[u][k]=ret;
            }else{
                int ret=0;
                for(auto v:adj[u]){
                    if(f[v][k+1]){
                        ret=1;
                        break;
                    }
                }
                f[u][k]=ret;
            }
        }
    }
    cout<<f[1][0];
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}