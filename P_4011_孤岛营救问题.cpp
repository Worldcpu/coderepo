#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e4+15,MM=50,AWA=1e6+16;
struct Edge{
    int v,w;
};
int n,m,p,K,S,cnt;
int pos[MN][MN];
int mp[MN][MN],kcnt[MM];
pir key[MM][MM];
vector<Edge> adj[AWA];
int dis[AWA];
bool vis[AWA];

void build(){
    int M=n*m;
    bool hk[MM];
    int maxn=1<<p;
    for(int i=0;i<maxn;i++){
        for(int j=1;j<=p;j++){
            if(i&(1<<(j-1))){
                hk[j]=1;
            }else hk[j]=0;
        }
        for(int j=1;j<=n;j++){
            for(int k=1;k<=m;k++){
                int x=pos[j][k],y=pos[j][k+1];
                if(mp[x][y]!=-1&&y){
                    if(mp[x][y]==0||hk[mp[x][y]]){
                        adj[i*M+x].push_back({i*M+y,1});
                        adj[i*M+y].push_back({i*M+x,1});
                    }
                }
                y=pos[j+1][k];
                if(mp[x][y]!=-1&&y){
                    if(mp[x][y]==0||hk[mp[x][y]]){
                        adj[i*M+x].push_back({i*M+y,1});
                        adj[i*M+y].push_back({i*M+x,1});
                    }
                }
            }
        }
        for(int j=1;j<=p;j++){
            if(!hk[j]){
                int h=i+(1<<(j-1));
                for(int k=1;k<=kcnt[j];k++){
                    int x=pos[key[j][k].first][key[j][k].second];
                    adj[i*M+x].push_back({h*M+x,0});
                }
            }
        }
    }
}

void spfa(){
    memset(dis,0x3f,sizeof(dis));
    queue<int> q;
    dis[pos[1][1]]=0;
    q.push(pos[1][1]);
    vis[pos[1][1]]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(auto e:adj[u]){
            if(dis[e.v]>dis[u]+e.w){
                dis[e.v]=dis[u]+e.w;
                if(!vis[e.v]){
                    vis[e.v]=1;
                    q.push(e.v);
                }
            }
        }
    }
}

int main(){
    cin>>n>>m>>p>>K;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            pos[i][j]=++cnt;
        }
    }
    for(int i=1;i<=K;i++){
        int x1,y1,x2,y2,g;
        cin>>x1>>y1>>x2>>y2>>g;
        int x=pos[x1][y1],y=pos[x2][y2];
        if(g==0) g=-1;
        mp[x][y]=mp[y][x]=g;
    }
    cin>>S;
    for(int i=1;i<=S;i++){
        int u,v,g;
        cin>>u>>v>>g;
        kcnt[g]++;
        key[g][kcnt[g]]=pir(u,v);
    }
    int ans=1e9;
    build();
    spfa();
    int end=pos[n][m];
    for(int i=0;i<(1<<p);i++){
        ans=min(ans,dis[i*n*m+end]);
    }
    if(ans<1e9) cout<<ans;
    else cout<<-1;
    return 0;
}