#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=223;
int mp[MN][MN],f[MN][MN],pre[MN][MN];
int dis[MN],n,m;
vector<int> path;

void output(int x,int y){
    if(pre[x][y]==0) return;
    output(x,pre[x][y]);
    path.push_back(pre[x][y]);
    output(pre[x][y],y);
}

int main(){
    memset(f,0x3f,sizeof(f));
    memset(mp,0x3f,sizeof(mp));
    memset(dis,0x3f,sizeof(dis));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        f[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        mp[u][v]=min(mp[u][v],w);
        mp[v][u]=min(mp[v][u],w);
        f[u][v]=mp[u][v];
        f[v][u]=mp[v][u];
    }
    ll ans=0x3f3f3f3f3f;
    for(int k=1;k<=n;k++){
        for(int i=1;i<k;i++){
            for(int j=i+1;j<k;j++){
                if(ans>(ll)f[i][j]+mp[j][k]+mp[k][i]){
                    ans=f[i][j]+mp[j][k]+mp[k][i];
                    path.clear();
                    path.push_back(i);
                    output(i,j);
                    path.push_back(j);
                    path.push_back(k);
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(f[i][j]>f[i][k]+f[k][j]){
                    f[i][j]=f[i][k]+f[k][j];
                    pre[i][j]=k;
                }
            }
        }
    }
    if(ans>=1e9) cout<<"No solution.";
    else{
        int cnt=0;
        for(auto awa:path){
            cnt++;
            if(cnt==path.size()) cout<<awa;
            else cout<<awa<<" ";
        }
    }
    return 0;
}