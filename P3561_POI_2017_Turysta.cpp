#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e3+15;
int n,tcnt,nxt[MN],a[MN][MN],in[MN],tpos[MN],pos[MN];
vector<int> adj[MN],G[MN],dcc[MN],ans[MN];

namespace Tarjan{
    int dfn[MN],low[MN],s[MN],col[MN],ctot,top,dtot;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        s[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(low[u]==dfn[u]){
            ctot++;
            int p;
            do{
                p=s[top--];
                col[p]=ctot;
                vis[p]=0;
            }while(p!=u);
        }
    }
}using namespace Tarjan;

void toposort(){
    queue<int> q;
    for(int i=1;i<=ctot;i++){
        if(!in[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        tpos[++tcnt]=u;
        pos[u]=tcnt;
        for(auto v:G[u]){
            in[v]--;
            if(!in[v]) q.push(v);
        }
    }
}

void getham(int c){
    if(dcc[c].size()==1) return;
    int s=dcc[c][0],t=s;
    for(int i=1;i<dcc[c].size();i++){
        int x=dcc[c][i];
        if(a[t][x]) nxt[t]=x,t=x;
        else if(a[x][s]) nxt[x]=s,s=x;
        else{
            for(int j=s;j!=t;j=nxt[j]){
                if(a[j][x]&&a[x][nxt[j]]){
                    nxt[x]=nxt[j];
                    nxt[j]=x;
                    break;
                }
            }
        }
    }
    t=0;
    for(int i=nxt[s];i;i=nxt[i]){
        if(t){
            if(a[i][s]){
                t=i;
                continue;
            }
            for(int j=s,k=nxt[s];j!=t;j=k,k=nxt[k]){
                if(a[i][k]){
                    nxt[j]=nxt[t];
                    nxt[t]=s;
                    s=k;
                    t=i;
                    break;
                }
            }
        }else if(a[i][s]) t=i;
    }
    nxt[t]=s;
}

int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i-1;j++){
            int x;
            cin>>x;
            if(x){
                adj[j].push_back(i);
                a[j][i]=1;
            }else{
                adj[i].push_back(j);
                a[i][j]=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) Tarjan::tarjan(i);
    }
    for(int i=1;i<=n;i++){
        dcc[col[i]].push_back(i);
    }
    for(int u=1;u<=n;u++){
        for(auto v:adj[u]){
            if(col[u]!=col[v]){
                G[col[u]].push_back(col[v]);
                in[col[v]]++;
            }
        }
    }
    toposort();
    for(int i=1;i<=tcnt;i++){
        getham(tpos[i]);
    }
    for(int i=1;i<=n;i++){
        int lst=i,now=pos[col[i]];
        while('QWQ'){
            if(dcc[tpos[now]].size()==1){
                ans[i].push_back(lst);
                if(now==tcnt) break;
                lst=dcc[tpos[++now]][0];
                continue;
            }
            ans[i].push_back(lst);
            for(int j=nxt[lst];j!=lst;j=nxt[j]){
                ans[i].push_back(j);
            }
            if(now==tcnt) break;
            lst=dcc[tpos[++now]][0];
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i].size()<<' ';
        for(auto p:ans[i]) cout<<p<<" ";
        cout<<'\n';
    }
    return 0;
}
