#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Node{
    int u,v,l,r,op;

    friend bool operator<(const Node &x,const Node &y){
        return x.l>y.l;
    }

};
int n,m,f[MN][2];
vector<Node> g[MN][2];
priority_queue<Node> q;

void update(int u,int v,int l,int r){
    int op=l&1;
    if(f[u][op]>=l){
        if(v==n){
            cout<<l+1;
            exit(0);
        }
        if(f[v][!op]<=r+1){
            f[v][!op]=r+1;
            for(auto p:g[v][!op]){
                q.push({p.u,p.v,l+1,p.r,0});
            }
            g[v][!op].clear();
        }
    }else g[u][op].push_back({u,v,l,r,0});
}

int main(){
    cin>>n>>m;
    if(n==1){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=m;i++){
        int u,v,l,r;
        cin>>u>>v>>l>>r;
        --r;
        int op=(r-l)&1;
        q.push({u,v,l,r-op,1});
        q.push({u,v,l+1,r-(!op),1});
    }
    memset(f,128,sizeof(f));
    f[1][0]=0;
    while(!q.empty()){
        auto f=q.top();
        q.pop();
        if(f.l>f.r) continue;
        update(f.u,f.v,f.l,f.r);
        if(f.op==1) update(f.v,f.u,f.l,f.r);
    }
    cout<<-1;
    return 0;
}