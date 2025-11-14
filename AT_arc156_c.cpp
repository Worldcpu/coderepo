#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,dg[MN],ans[MN];
vector<int> adj[MN];

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(dg[i]==1) q.push(i);
    }
    while(q.size()>=2){
        int x=q.front();
        q.pop();
        int y=q.front();
        q.pop();
        ans[y]=x,ans[x]=y;
        for(auto v:adj[x]){
            if(--dg[v]==1){
                q.push(v);
            }
        }
        for(auto v:adj[y]){
            if(--dg[v]==1){
                q.push(v);
            }
        }
    }
    if(q.size()==1){
        ans[q.front()]=q.front();
        q.pop();
    }
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        dg[u]++,dg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    toposort();
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }

    return 0;
}