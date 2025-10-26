#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,m,ans;
vector<int> adj[MN];
set<int> st[MN];

namespace DSU{
    int pre[MN];

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    void initpre(){
        for(int i=0;i<MN;i++) pre[i]=i;
    }

}using namespace DSU;

void merge(int x,int y){
    if(st[x].size()<st[y].size()) swap(st[x],st[y]);
    for(auto p:st[y]) st[x].insert(p);
    st[y].clear();
}

void maintain(int x,int lim){
    while(!st[x].empty()&&(*st[x].begin())<=lim) st[x].erase(st[x].begin());
}

void init(){
    initpre();
}


signed main(){
    init();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        for(auto v:adj[i]){
            if(v>i) st[i].insert(v);
        }
        int tmp=st[i].size();
        for(auto v:adj[i]){
            if(v<i&&i!=root(v)){
                merge(i,root(v));
                pre[root(v)]=i;
            }
        }
        maintain(i,i);
        ans+=st[i].size()-tmp;       
    }
    cout<<ans;

    return 0;
}