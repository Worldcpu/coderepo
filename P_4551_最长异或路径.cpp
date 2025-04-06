#include<bits/stdc++.h>
using namespace std;
const int MN=1e7+15;
struct node{
    int num;
    int son[2];
    bool isend;
}t[MN];

struct edge{
    int v,w;
};

int cnt=1,n;

vector<edge> adj[MN];
int dis[MN];

void dfs(int u,int fa){
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa) continue;
        dis[v]=(w^dis[u]);
        dfs(v,u);
    }
}

void insert(int x){
    int now=0;
    for(int i=31;i>=0;i--){
        int ch=((x>>i)&1);
        if(!t[now].son[ch]){
            t[now].son[ch]=cnt++;
        }
        now=t[now].son[ch];
    }
    t[now].isend=1;
}

int query(int x){
    int now=0,ans=0;
    for(int i=31;i>=0;i--){
        int ch=((x>>i)&1);
        if(t[now].son[ch^1]){
            ans+=(1<<i);
            now=t[now].son[ch^1];
        }else now=t[now].son[ch];
    }
    return ans;
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs(1,0);
    int ret=0;
    for(int i=1;i<=n;i++){
        insert(dis[i]);
    }
    
    for(int i=1;i<=n;i++){
        ret=max(ret,query(dis[i]));
    }

    cout<<ret;
    return 0;
}