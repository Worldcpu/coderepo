#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#define pir pair<int,int>
#define ll long long
using namespace std;
const int MN=13,INF=0x3f3f3f3f;
int mc[MN][MN],n,m,ex[1<<MN],road[1<<MN][MN];
ll ans=INF;
ll f[MN][1<<MN];
vector<pir> cost[1<<MN];
int main(){
    memset(mc,0x3f,sizeof(mc));
    memset(road,0x3f,sizeof(road));
    memset(f,0x3f,sizeof(f));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        mc[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        mc[u][v]=mc[v][u]=min(mc[u][v],w);
    }
    for(int i=0;i<(1<<n);i++){
        ex[i]=i;
        for(int j=1;j<=n;j++){
            if(!((i>>(j-1))&1))continue;
            road[i][j]=0;
            for(int k=1;k<=n;k++){
                if(mc[j][k]>=INF||((i>>(k-1))&1)) continue;
                road[i][k]=min(road[i][k],mc[j][k]);
                ex[i]|=(1<<(k-1));
            }
        }
    }
    for(int i=0;i<(1<<n);i++){
        for(int j=i;j;j=(j-1)&i){
            if((ex[j]&i)!=i) continue;
            int cst=0;
            for(int k=1;k<=n;k++){
                if(((j^i)>>(k-1))&1){
                    cst+=road[j][k];
                }
            }
            cost[i].push_back(pir(j,cst));
        }
    }
    for(int i=1;i<=n;i++){
        f[1][1<<(i-1)]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<n);j++){
            for(auto p:cost[j]){
                f[i][j]=min(f[i][j],f[i-1][p.first]+(i-1)*p.second);
            }
        }
    }
    for(int i=1;i<=n;i++){
        ans=min(ans,f[i][(1<<n)-1]);
    }
    cout<<ans;
    return 0;
}