#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=17;
struct Edge{
    int v,w;
};
int op[1<<MN],dis[1<<MN],T,a0,a1,a2,a3,m,msk=0;
bool vis[1<<MN];
vector<Edge> adj[1<<MN];

void dijk(int st){
    priority_queue<pir,vector<pir>,greater<pir>> q;
    memset(dis,0x3f,sizeof(dis));
    dis[st]=0;
    q.push(pir(0,st));
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(dis[e.v]>dis[u]+e.w){
                dis[e.v]=dis[u]+e.w;
                q.push(pir(dis[e.v],e.v));
            }
        }
    }
}

void init(){
    op[0]=min({8*a0,4*a1,4*a2,2*a3});
    op[1]=op[2]=op[4]=op[8]=a0;
    op[3]=op[12]=min(2*a0,a1);
    op[5]=op[10]=min(2*a0,a2);
    op[6]=op[9]=min(2*a0,a1+a2);
    op[7]=op[11]=op[13]=op[14]=min({3*a0,a0+a3,a0+a1+a2});
    op[15]=min({4*a0,a3,2*a1,2*a2});
    for(int s=0;s<(1<<16);s++){
        for(int i=0;i<16;i++){
            int nxt=0,w=op[i];
            for(int j=0;j<(1<<4);j++){
                if(s&(1<<j)){
                    int nxtt=j^i;
                    if(nxtt!=15) nxt|=(1<<nxtt);
                }
            }
            adj[nxt].push_back({s,w});
        }
    }
    dijk(0);
}

void solve(){
    cin>>m;
    msk=0;
    for(int i=1;i<=m;i++){
        int x=0;
        string st;
        cin>>st;
        x+=((st[0]-'0')<<3);
        x+=((st[1]-'0')<<2);
        cin>>st;
        x+=((st[0]-'0')<<1);
        x+=((st[1]-'0')<<0);
        msk|=(1<<x);
    }
    cout<<dis[msk]<<'\n';
}

int main(){
    cin>>T>>a0>>a1>>a2>>a3;
    init();
    while(T--){
        solve();
    }


    return 0;
}