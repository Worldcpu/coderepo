#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,a[MN],b[MN],c[MN],in[MN],p[MN],ans[MN];
vector<int> adj[MN],B[MN];

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++) if(!in[i]) q.push(i);
    int l=1,r=n;
    while(!q.empty()){
        int u=q.front(),w[2]{}; q.pop();
        for(auto v:B[u]){
            if(p[a[v]]&&p[c[v]]) continue;
            if(p[a[v]]){
                if(p[a[v]]<=l) w[0]++;
                if(p[a[v]]>=r) w[1]++;
            }
            if(p[c[v]]){
                if(p[c[v]]<=l) w[0]++;
                if(p[c[v]]>=r) w[1]++;
            }
        }
        for(auto v:adj[u]){
            if(p[a[v]]&&!p[b[v]]){
                if(p[a[v]]<=l) w[1]++;
                if(p[a[v]]>=r) w[0]++;
            }
            if(p[c[v]]&&!p[b[v]]){
                if(p[c[v]]<=l) w[1]++;
                if(p[c[v]]>=r) w[0]++;
            }
            if(!p[a[v]]&&!p[c[v]]) if(!--in[b[v]]) q.push(b[v]);
        }
        p[u]=w[0]<w[1]?r--:l++;
        if(l>r) break;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i]>>c[i];
        in[b[i]]++;
        B[b[i]].push_back(i);
        adj[a[i]].push_back(i);
        adj[c[i]].push_back(i);       
    }
    toposort();
    for(int i=1;i<=n;i++) ans[p[i]]=i;
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    return 0;
}
