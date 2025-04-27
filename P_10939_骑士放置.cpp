#include<bits/stdc++.h>
#define pos(x,y) (((x-1)*m+y))
using namespace std;
constexpr int MN=520,MP=8e5+15;
int dx[8]={-1,-2,-2,-1,1,2,2,1};
int dy[8]={-2,-1,1,2,-2,-1,1,2};
int n,m,t,p[MP];
vector<int> adj[MP];
bool stop[MN][MN],vis[MP];

bool dfs(int u){
    for(auto v:adj[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!p[v]||dfs(p[v])){
                p[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=t;i++){
        int x,y;
        cin>>x>>y;
        stop[x][y]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(stop[i][j]||((i&1)!=(j&1))) continue;
            for(int k=0;k<8;k++){
                int fx=i+dx[k],fy=j+dy[k];
                if(fx>=1&&fx<=n&&fy>=1&&fy<=m && (!stop[fx][fy])){
                    adj[pos(i,j)].push_back(pos(fx,fy));
                }
            }
        }
    }
    int ans=n*m-t;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(stop[i][j]||((i&1)!=(j&1))) continue;
            memset(vis,0,sizeof(vis));
            ans-=dfs(pos(i,j));
        }
    }
    cout<<ans;
    return 0;
}