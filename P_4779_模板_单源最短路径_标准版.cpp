#include<iostream>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
const int MN=2e5+15;
struct edge
{
    int v,w;
};
struct node
{
    int pos,dis;
    bool operator<(const node&x)const{
        return x.dis<dis;
    }
};

int n,m,s,ans[MN];
bool vis[MN];
priority_queue<node> q;
vector<edge> adj[MN];
void djl(){
    while (!q.empty())
    {
        node f=q.top();
        q.pop();
        int fp=f.pos,fdis=f.dis;
        if(vis[fp]) continue;
        vis[fp]=1;
        for(auto v:adj[fp]){
            if(ans[v.v]>v.w+ans[fp]){
                ans[v.v]=ans[fp]+v.w;
                if(!vis[v.v]){
                    q.push({v.v,ans[v.v]});
                }
            }
        }
    }
    
}
int main(){
    memset(ans,0x3f,sizeof(ans));
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    ans[s]=0;
    q.push({s,0});
    djl();
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}