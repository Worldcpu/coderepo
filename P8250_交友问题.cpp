#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15,MB=40;
int n,m,q,id[MN];
vector<int> adj[MN];
vector<bitset<MN>> bit;
map<int,int> mp[MN];

signed main(){
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        mp[u][v]=mp[v][u]=1;
    }
    for(int i=1;i<=n;i++){
        if(adj[i].size()>MB){
            id[i]=bit.size();
            bit.push_back(0);
            bit[id[i]][i]=1;
            for(auto v:adj[i]){
                bit[id[i]][v]=1;
            }
        }
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        if(adj[x].size()<MB){
            int ans=0;
            for(auto v:adj[x]){
                if(!mp[v][y]&&y!=v){
                    ans++;
                }
            }
            cout<<ans<<'\n';
        }else{
            if(adj[y].size()>MB){
                auto bitt=(bit[id[x]]^(bit[id[x]]&bit[id[y]]));
                bitt[x]=0;
                cout<<bitt.count()<<'\n';
            }else{
                auto bitt=bit[id[x]];
                for(auto v:adj[y]){
                    bitt[v]=0;
                }
                bitt[x]=bitt[y]=0;
                cout<<bitt.count()<<'\n';
            }
        }
    }
    return 0;
}

