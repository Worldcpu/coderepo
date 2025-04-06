#include<iostream>
#include<cstring>
using namespace std;
const int MN=515;
bool map[MN][MN],vis[MN];
int n,m,e,p[MN];
bool match(int u){
    for(int i=1;i<=m;i++){
        if(map[u][i]&&!vis[i]){
            vis[i]=1;
            if(!p[i]||match(p[i])){
                p[i]=u;
                return 1;
            }
        }
    }
    return 0;
}
void solve(){
    int ans=0;
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans+=match(i);
    }
    cout<<ans;
    return;
}
int main(){
    cin>>n>>m>>e;
    for(int i=1;i<=e;i++){
        int u,v;
        cin>>u>>v;
        map[u][v]=1;
    }
    solve();
    return 0;
}