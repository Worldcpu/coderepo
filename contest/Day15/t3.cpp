#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3520;
struct Node{
    int u,top,fa;
};
int n,ans,fa[MN],cnt[MN],dis[MN],ltop[MN];
int vis[MN];
vector<int> adj[MN],pdis[MN];

void bfs(int st){
    queue<int> q;
    for(auto v:adj[st]){
        dis[v]=1;
        ltop[v]=v;
        q.push(v);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(dis[v]==-1){
                dis[v]=dis[u]+1;
                ltop[v]=ltop[u];
                q.push(v);
            }
        }
    }

}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>fa[i];
        if(!fa[i]) continue;
        adj[fa[i]].push_back(i);
        adj[i].push_back(fa[i]);
    }
    for(int u=1;u<=n;u++){
        int maxd=-1;
        for(int j=1;j<=n;j++){
            ltop[j]=0;
            dis[j]=-1;
            vis[j]=0;
            pdis[j].clear();
        }
        dis[u]=0;
        bfs(u);
        for(int j=1;j<=n;j++){
            maxd=max(maxd,dis[j]);
        }
        for(int j=1;j<=n;j++){
            if(j!=u&&dis[j]>0) pdis[dis[j]].push_back(j);
        }
        for(int j=1;j<=maxd;j++){
            if(pdis[j].empty()) continue;
            int sum1=0,sum2=0,sum3=0;
            vector<int> cntt;
            for(auto p:pdis[j]){
                int top=ltop[p];
                if(vis[top]!=j){
                    vis[top]=j;
                    cntt.push_back(top);
                }
            }
            for(auto c:cntt) cnt[c]=0;
            for(auto p:pdis[j]){
                int top=ltop[p];
                cnt[top]++;
            }
            for(auto c:cntt){
                sum1+=cnt[c];
                sum2+=cnt[c]*cnt[c];
                sum3+=cnt[c]*cnt[c]*cnt[c];
            }
            ans+=(sum1*sum1*sum1-3*sum1*sum2+2*sum3)/6;  // TIME USED: 9:32 -> 10:45         
        }
    }
    cout<<ans;

    return 0;
}