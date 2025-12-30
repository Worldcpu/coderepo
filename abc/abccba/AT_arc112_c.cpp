#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,f[MN];
vector<int> adj[MN];

namespace Tree{
    int fa[MN],siz[MN];

    struct Node{
        int x;

        friend bool operator<(const Node &x,const Node &y){
            int xx=x.x,yx=y.x;
            return siz[xx]-f[xx]-f[xx]<siz[yx]-f[yx]-f[yx];
        }
    };

    void dfs1(int u,int pre){
        f[u]=1,siz[u]=1;
        priority_queue<Node> q;
        int tmp1=0,tmp2=0;

        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[v]%2==0){
                if(siz[v]-f[v]>=f[v]){
                    f[u]+=f[v];
                }else{
                    tmp1+=f[v];
                    tmp2+=siz[v]-f[v];
                }
            }else{
                q.push({v});
            }
        }
        int r=1;
        while(!q.empty()){
            auto tp=q.top().x;
            q.pop();
            if(r) f[u]+=f[tp];
            else f[u]+=siz[tp]-f[tp];
            r^=1;
        }
        if(r) f[u]+=tmp1;
        else f[u]+=tmp2;
    }

}using namespace Tree;

int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        adj[fa[i]].push_back(i);
    }
    dfs1(1,0);
    cout<<f[1];

    return 0;
}