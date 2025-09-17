#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=3e5+15;
struct Node{
    int j,cst;

    bool operator<(const Node &x)const{
        return cst<x.cst;
    }

};
int n,m,dep[MN],ans,tag[MN];
bool flag=1;
vector<int> adj[MN];
vector<pir> path[MN];
multiset<Node> st[MN];

void merge(int x,int y){
    if(st[x].size()<st[y].size()) swap(st[x],st[y]),swap(tag[x],tag[y]); 
    int mnx=(!st[x].size())?0:(*st[x].begin()).cst,mny=(!st[y].size())?0:(*st[y].begin()).cst;
    while(!st[y].empty()){
        auto tp=(*st[y].begin());
        st[y].erase(st[y].begin());
        tp.cst+=mnx-mny;
        st[x].insert(tp);
    }
    tag[x]+=mny+tag[y];
}

void dfs1(int u,int pre){
    dep[u]=dep[pre]+1;
    for(auto v:adj[u]){
        if(v==pre||!flag) continue;
        dfs1(v,u);
        merge(u,v);
    }
    if(!flag) return;
    int minn=0;
    if(!st[u].empty()) minn=(*st[u].begin()).cst;
    for(auto p:path[u]){
        st[u].insert({p.first,p.second+minn});
    }
    if(st[u].empty()){
        flag=0;
        return;
    }
    if(u!=1){
        while(!st[u].empty()&&dep[(*st[u].begin()).j]>=dep[u]) st[u].erase(st[u].begin());
        if(st[u].empty()){
            flag=0;
            return;
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        path[u].push_back(pir(v,w));
    }
    dfs1(1,0);
    if(!flag){
        cout<<-1;
        return 0;
    }
    else if(m==1) cout<<0;
    else cout<<st[1].begin()->cst+tag[1];

    return 0;
}