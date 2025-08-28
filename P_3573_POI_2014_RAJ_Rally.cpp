#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,ans1,ans2,tcnt,dg[MN],tps[MN],dis1[MN],dis2[MN];
vector<int> adj[MN],fadj[MN];

struct Queue{
    priority_queue<int>a,b;
    void push(int x){a.push(x);}
    void pop(int x){b.push(x);}
    int top(){while(!b.empty()&&a.top()==b.top())a.pop(),b.pop();return a.top();}
}Q;

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!dg[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        tps[++tcnt]=u;
        for(auto v:adj[u]){
            if(--dg[v]==0) q.push(v);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);   
        fadj[v].push_back(u);    
        dg[v]++;
    }
    toposort();
    for(int i=1;i<=n;i++){
        int u=tps[i];
        for(auto v:adj[u]){
            dis1[v]=max(dis1[v],dis1[u]+1);
        }
    }
    for(int i=n;i>=1;i--){
        int u=tps[i];
        for(auto v:fadj[u]){
            dis2[v]=max(dis2[v],dis2[u]+1);
        }
    }
    for(int i=1;i<=n;i++) Q.push(dis2[i]);
    ans1=Q.top();
    for(int i=1;i<=n;i++){
        int u=tps[i];
        Q.pop(dis2[u]);  
        for(auto v:fadj[u]){
            Q.pop(dis1[u]+dis2[v]+1); 
        }
        int ret=Q.top();
        if(ret<=ans1){
            ans1=ret;
            ans2=u;
        }
        for(auto v:adj[u]){
            Q.push(dis1[u]+dis2[v]+1); 
        }
        Q.push(dis1[u]); 
    }

    cout<<ans2<<" "<<ans1<<"\n";
    return 0;
}
