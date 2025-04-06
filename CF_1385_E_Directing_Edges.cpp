#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
const int MN=1e6+15;
struct edge{
    int v;
    bool op;
};
map<pir,int> mp;
int T,n,m,in[MN],hd[MN],tot;
bool vis[MN];
vector<edge> adj[MN];
vector<int> topo;
vector<pir> ans;
bool toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!in[i]&&hd[i]) q.push(i);
    }
    
    while (!q.empty()){
        int f=q.front();
        q.pop();
        vis[f]=1;
        topo.push_back(f);
        for(auto e:adj[f]){
            int v=e.v,eop=e.op;
            if(!eop) continue;
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
    if(topo.size()!=tot) return 0;
    return 1;
}

void dfs(int u,int fa){
    for(auto e:adj[u]){
        int v=e.v,eop=e.op;
        if(!eop&&v==fa) continue;
        ans.push_back(pir(u,v));
    }
}

int main(){
    cin>>T;
    while(T--){
        mp.clear();
        topo.clear();
        tot=0;
        ans.clear();
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            adj[i].clear();
            vis[i]=0;
            hd[i]=in[i]=0;
        }
        for(int i=1;i<=m;i++){
            int op,x,y;
            cin>>op>>x>>y;
            if(op==0){
                adj[x].push_back({y,0});
                adj[y].push_back({x,0});
            }else{
                mp[pir(x,y)]=mp[pir(y,x)]=1;
                adj[x].push_back({y,1});
                hd[x]=hd[y]=1;
                in[y]++;
            }
        }

        for(int i=1;i<=n;i++){
            if(hd[i]) tot++;
        }

        if(!toposort()){ 
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                for(auto &v:adj[i]){
                    if(mp[pir(i,v.v)]||mp[pir(v.v,i)]) continue;
                    v.op=1;
                    mp[pir(i,v.v)]=mp[pir(v.v,i)]=1;
                }
            }
        }
        
        for(int i=0;i<topo.size();i++){
            int u=topo[i];
            for(auto &e:adj[u]){
                int v=e.v,eop=e.op;
                if(mp[pir(u,v)]||mp[pir(v,u)])continue;
                e.op=1;
                mp[pir(u,v)]=mp[pir(v,u)]=1;
            }
        }

        for(int i=1;i<=n;i++){
            for(auto e:adj[i]){
                if(!e.op) continue;
                cout<<i<<" "<<e.v<<'\n';
            }
        }
    }
    return 0;
}