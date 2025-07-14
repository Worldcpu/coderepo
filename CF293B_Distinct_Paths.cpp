#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=1e9+7;
int n,m,K,mp[11][11],f[11][11];
bool vis[11];

int dfs(int x,int y){
    if(y>m){
        x++,y=1;
    }
    if(x>n) return 1;
    int st=f[x-1][y]|f[x][y-1],cnt=K,ret=0,t=-1;
    for(int i=1;i<=K;i++){
        if((st>>(i-1))&1) cnt--;
    }
    if(cnt<=(n-x)+(m-y)) return 0;
    for(int i=1;i<=K;i++){
        if((mp[x][y]&&mp[x][y]!=i)||((st>>(i-1))&1)){
            continue;
        }
        f[x][y]=st|(1<<(i-1));
        if(vis[i]) (ret+=dfs(x,y+1))%=MOD;
        else{
            vis[i]=1;
            if(t==-1) t=dfs(x,y+1);
            (ret+=t)%=MOD;
            vis[i]=0;
        }
    }
    return ret;
}

signed main(){
    cin>>n>>m>>K;
    if(n+m-1>K){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            vis[mp[i][j]]=1;
        }
    }
    cout<<dfs(1,1);
    return 0;
}
