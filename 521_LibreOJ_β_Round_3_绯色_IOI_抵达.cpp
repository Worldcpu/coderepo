#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,dg[MN],cnt,ans[MN],tot,in[MN];
vector<int> adj[MN],G[MN];

void topo1(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(dg[i]==1) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        int t=-1;
        for(auto v:adj[u]){
            if(dg[v]>0){
                t=v;
                dg[v]=0;
            }
        }
        if(t==-1){
            continue;
        }
        for(auto v:adj[u]){
            if(t==v) continue;
            G[t].push_back(v);
            in[v]++;
        }
        for(auto v:adj[t]){
            if(u==v) continue;
            G[u].push_back(v);
            in[v]++;
        }
        for(auto v:adj[t]){
            --dg[v];
            if(dg[v]==1){
                q.push(v);
            }
        }
        cnt++;
    }
}

void topo2(){
    priority_queue<int,vector<int>,greater<int>> q;
    for(int i=1;i<=n;i++){
        if(!in[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.top();
        q.pop();
        ans[++tot]=u;
        for(auto v:G[u]){
            in[v]--;
            if(!in[v]) q.push(v);
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        dg[u]++,dg[v]++;
    }
    topo1();
    if(cnt<n/2||n%2){
        cerr<<"QWQ\b";
        cout<<-1;
        return 0;
    }
    topo2();
    if(tot!=n){
        cerr<<"PWP\n";
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=tot;i++) cout<<ans[i]<<' ';
    return 0;
}