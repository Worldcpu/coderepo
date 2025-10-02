#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int st,ed,ans,n;
vector<int> adj[MN];

namespace Tarjan{
    int dfn[MN],low[MN],dtot;

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        int ch=0;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                if(u==st) ch++;
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]&&u!=st&&u!=ed&&dfn[v]<=dfn[ed]){
                    ans=min(ans,u);
                }
            }else low[u]=min(low[u],dfn[v]);
        }
    }
}

int main(){
    cin>>n;
    while(1){
        int u,v;
        cin>>u>>v;
        if(!u&&!v) break;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }   
    cin>>st>>ed;
    ans=n+1;
    Tarjan::tarjan(st);
    if(ans==n+1){
       cout<<"No solution"; 
    }else cout<<ans;
    return 0;
}