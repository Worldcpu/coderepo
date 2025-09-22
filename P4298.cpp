#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,m,ans1,col[MN],ctot;
bool mp[MN][MN],isdel[MN],ans2[MN],ans3[MN];

namespace Hungry{
    int p[MN];
    bool vis[MN];

    bool match(int u){
        if(isdel[u]) return 0;
        for(int v=1;v<=n;v++){
            if(!mp[u][v]||isdel[v]) continue;
            if(!vis[v]){
                vis[v]=1;
                if(!p[v]||match(p[v])){
                    p[v]=u;
                    return 1;
                }
            }
        }
        return 0;
    }

}using namespace Hungry;

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        mp[u][v]=1;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                mp[i][j]|=(mp[i][k]&&mp[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans1+=match(i);
    }
    cout<<n-ans1<<'\n';
    for(int i=1;i<=n;i++){
        memset(isdel,0,sizeof(isdel));
        memset(p,0,sizeof(p));
        int tot=n;
        for(int j=1;j<=n;j++){
            if(mp[i][j]||mp[j][i]||i==j){
                isdel[j]=1;
                tot--;
            }
        }
        int ret=0;
        for(int j=1;j<=n;j++){
            memset(vis,0,sizeof(vis));
            ret+=match(j);
        }
        ans3[i]=(tot-ret==n-ans1-1);
    }
    for(int i=1;i<=n;i++){
        if(ans3[i]&&!col[i]){
            ++ctot;
            ans2[i]=1;
            for(int j=1;j<=n;j++){
                if(mp[i][j]||mp[j][i]||i==j){
                    col[j]=ctot;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans2[i];
    }
    cout<<'\n';
    for(int i=1;i<=n;i++){
        cout<<ans3[i];
    }

    return 0;
}