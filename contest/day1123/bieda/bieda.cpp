#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
struct Edge{
    int v,id;
};
struct Node{
    int x,y,c,id;
}a[MN];
int n,ans[MN];

struct Graph{
    int dg[MN];
    vector<Edge> adj[MN];

    void uadd(int u,int v,int id=0){
        adj[u].push_back({v,id});
        dg[u]++;
        adj[v].push_back({u,id}); 
        dg[v]++;
    }

    void dadd(int u,int v,int id=0){
        adj[u].push_back({v,id});
        dg[u]++;
    }

    auto& operator[](int u){
        return adj[u];
    }
}g1,g2,g3;

namespace Euler{
    int dg[3][MN],cur[MN],st[MN],top,bel[MN],etot,nowc,col[MN];
    bool vis1[MN],vis2[MN],vis3[MN];

    void dfs1(int u,int pre){
        if(vis1[u]){
            etot++;
            while(top){
                bel[st[top--]] = etot;
            }
            return;
        }
        vis1[u]=1;
        st[++top]=u;
        for(auto e:g1[u]){
            int v=e.v,id=e.id;
            if(v==pre) continue;
            dfs1(v,u);
        }
    }

    void initeuler(int n,int m){
        nowc=0;
        fill(cur, cur + n + 1, 0);       
        fill(vis2, vis2 + n + 1, false);  
        fill(vis3, vis3 + m + 1, false);   
    }

    void dfs2(int u){
        vis2[u]=1;
        while(cur[u] < (int)g2[u].size()){
            auto [v,id] = g2[u][cur[u]++];
            if(!vis3[id]){
                vis3[id]=1;
                dfs2(v);
                col[id]=nowc;
                nowc^=1;
            }
        }
    }

    void dfs3(int u,int c){
        vis2[u]=1;
        while(cur[u] < (int)g2[u].size()){
            auto [v,id] = g2[u][cur[u]++];
            if(!vis3[id] && col[id]==c){
                vis3[id]=1;
                dfs3(v,c);
                ans[id]=((c<<1)|nowc)+1;
                nowc^=1;
            }
        }
    }

}using namespace Euler;

bool cmpx(Node A, Node B){
    if(A.x != B.x) return A.x < B.x;
    return A.y < B.y;
}

bool cmpy(Node A, Node B){
    if(A.y != B.y) return A.y < B.y;
    return A.x < B.x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        char qwq;
        cin>>a[i].x>>a[i].y>>qwq;
        if(qwq=='/') a[i].c=0;
        else a[i].c=1;
        a[i].id=i;
    }

    sort(a+1,a+1+n,cmpx);
    for(int i=1,j;i<=n;i=j+1){
        j=i;
        while(j<n && a[i].x==a[j+1].x) j++;
        for(int k=i;k<j;k++){
            g1.uadd(a[k].id + n, a[k+1].id);
        }
    }

    sort(a+1,a+1+n,cmpy);
    for(int i=1,j;i<=n;i=j+1){
        j=i;
        while(j<n && a[i].y==a[j+1].y) j++;
        for(int k=i;k<j;k++){
            if(a[k].c==0){
                if(a[k+1].c==0){
                    g1.uadd(a[k].id, a[k+1].id + n);
                }else{
                    g1.uadd(a[k].id, a[k+1].id);
                }
            }else if(a[k+1].c==0){
                g1.uadd(a[k].id + n, a[k+1].id + n);
            }else{
                g1.uadd(a[k].id + n, a[k+1].id);
            }
        }
    }

    for(int i=1;i<=2*n;i++){
        if(!vis1[i]){
            top=0;
            dfs1(i,0);
        }
    }

    for(int i=1;i<=n;i++){
        g2.uadd(bel[i], bel[i+n], i);
    }
    for(int i=1;i<=etot;i++){
        if(g2.dg[i]%8!=0){
            cout<<-1<<'\n';
            return 0;
        }
    }
    while(g2.dg[0]%8!=0){
        g2.dadd(0,0,0); 
    }
    initeuler(etot,n);
    for(int i=0;i<=etot;i++){
        if(!vis2[i]) dfs2(i);
    }
    initeuler(etot,n);
    for(int i=0;i<=etot;i++){
        if(!vis2[i]) dfs3(i,0);
    }
    initeuler(etot,n);
    for(int i=0;i<=etot;i++){
        if(!vis2[i]) dfs3(i,1);
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    cout<<"\n";
    return 0;
}
