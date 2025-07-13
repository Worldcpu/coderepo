#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5200;
int dis[MN][MN],a[MN],cnt[MN],c[MN][5],n,m,K,ans;
bool vis[MN];
vector<int> adj[MN];

void bfs(){
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++){
        queue<int> q;
        dis[i][i]=0;
        q.push(i);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u]){
                if(dis[i][v]>dis[i][u]+1){
                    dis[i][v]=dis[i][u]+1;
                    if(dis[i][v]>=K) continue;
                    q.push(v);
                }
            }
        }
    }
}

signed main(){
    cin>>n>>m>>K;
    K++; 
    for(int i=2;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bfs();
    for(int i=2;i<=n;i++){
        priority_queue<pir> q;
        for(int j=2;j<=n;j++){
            if(i==j) continue;
            if(dis[1][j]<=K&&dis[j][i]<=K){ 
                q.push(pir(a[j],j));
            }
        }
        while(!q.empty()&&cnt[i]<3){
            c[i][++cnt[i]]=q.top().second;
            q.pop();
        }
    }
    for(int i=2;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(dis[i][j]>K) continue;            
            for(int k=1;k<=cnt[i];k++){
                for(int p=1;p<=cnt[j];p++){
                    int u=c[i][k],v=c[j][p];                    
                    if(u!=j&&v!=i&&u!=v){
                        ans=max(ans,a[i]+a[j]+a[u]+a[v]);
                    }
                }
            }
        }
    }
    cout<<ans;
    return 0;
}
