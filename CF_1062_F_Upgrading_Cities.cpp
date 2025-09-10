#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,a[MN],b[MN],dg[MN],ans[MN];
vector<int> adj[MN];

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!dg[i]) q.push(i);
    }
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ++cnt;
        if(q.empty()){
            ans[u]+=n-cnt;
        }else if(q.size()==1){
            int uu=q.front();
            bool flag=1;
            for(auto v:adj[uu]){
                if(dg[v]==1){
                    flag=0;
                    break;
                }
            }
            if(flag) ans[u]+=n-cnt-1;
        }
        for(auto v:adj[u]){
            if(!--dg[v]) q.push(v);
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i];
        adj[a[i]].push_back(b[i]);
        dg[b[i]]++;
    }
    toposort();
    for(int i=1;i<=n;i++){
        adj[i].clear();
    }
    for(int i=1;i<=m;i++){
        adj[b[i]].push_back(a[i]);
        dg[a[i]]++;
    }
    toposort();
    int ret=0;
    for(int i=1;i<=n;i++){
        ret+=(ans[i]>=n-2);
    }
    cout<<ret;
    return 0;
}