#include<bits/stdc++.h>
using namespace std;

constexpr int MN=5005;
constexpr double INF=1e18,eps=1e-8;

struct Edge{
    int v;
    double w;
    int op;
};

int n,s,t;
vector<Edge> adj[MN];

namespace SPFA{
    double dis[MN];
    int cnt[MN];
    bool vis[MN];

    void init(){
        for(int i=0;i<=n+1;i++){
            dis[i]=-INF;
            cnt[i]=0;
            vis[i]=0;
        }
    }

    bool spfa(double k){
        init();
        queue<int> q;
        dis[n+1]=0;
        q.push(n+1);
        vis[n+1]=1;

        while(!q.empty()){
            int u=q.front(); q.pop();
            vis[u]=0;
            for(auto e:adj[u]){
                double w=e.w;
                if(e.op==1) w=log2(e.w - k);
                else if(e.op==2) w=-log2(e.w + k);
                if(dis[e.v]<dis[u]+w){
                    dis[e.v]=dis[u]+w;
                    cnt[e.v]=cnt[u]+1; 
                    if(cnt[e.v]>=n+2) return true; 
                    if(!vis[e.v]){
                        vis[e.v]=1;
                        q.push(e.v);
                    }
                }
            }
        }
        return 0;
    }
} using namespace SPFA;

int main(){
    cin>>n>>s>>t;
    for(int i=0;i<=n;i++) adj[n+1].push_back({i,0,3});
    for(int i=1;i<=s;i++){
        int op,a,b; double x;
        cin>>op>>a>>b>>x;
        adj[b].push_back({a,x,op});
    }
    for(int i=1;i<=t;i++){
        int c; 
        double x;
        cin>>c>>x;
        adj[0].push_back({c,log2(x),3});
        adj[c].push_back({0,-log2(x),3});
    }
    if(!spfa(0)){
        cout<<-1<<"\n";
        return 0;
    }
    double l=0,r=10,ans;
    while(r-l>eps){
        double mid=(l+r)/2.0;
        if(spfa(mid)) ans=mid,l=mid+eps;
        else r=mid-eps;
    }

    cout<<fixed<<setprecision(8)<<ans<<"\n";
    return 0;
}
