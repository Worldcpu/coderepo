#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
struct Query{
    int op,x,y;
}q[MN];
int n,m,ans[MN];
vector<int> adj[MN];


struct DSU{

    struct{
        int x,y,add;
    }s[MN];

    int top,pre[MN],siz[MN];

    DSU(){
        for(int i=1;i<MN;i++){
            pre[i]=i;
            siz[i]=1;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        return root(pre[x]);
    }

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(siz[rx]>siz[ry]) swap(rx,ry);
        s[++top]={rx,ry,siz[rx]==siz[ry]};
        pre[rx]=ry;
        if(siz[rx]==siz[ry]) siz[ry]++;
    }

    void rollback(int num){
        while(top>num&&top){
            auto p=s[top--];
            siz[pre[p.x]]-=p.add;
            pre[p.x]=p.x;
        }
    }

}dsu;

void dfs(int u){
    int lsttop=dsu.top;
    if(q[u].op==1){
        dsu.merge(q[u].x,q[u].y);
    }else if(q[u].op==3){
        ans[u]=(dsu.root(q[u].x)==dsu.root(q[u].y));
    }
    for(auto v:adj[u]){
        dfs(v);
    }
    dsu.rollback(lsttop);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>q[i].op;
        if(q[i].op==2){
            cin>>q[i].x;
            adj[q[i].x].push_back(i);
        }else{
            cin>>q[i].x>>q[i].y;
            adj[i-1].push_back(i);
        }
    }
    dfs(1);
    for(int i=1;i<=m;i++){
        if(q[i].op==3) cout<<ans[i]<<'\n';
    }
    return 0;
}
