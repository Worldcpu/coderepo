#include<bits/stdc++.h>
#define il inline
using namespace std;
il void read(int &x){
    x=0;bool flag=0;char ch=getchar();
    while (!(isdigit(ch)||ch=='-')&&ch!=EOF) ch=getchar();
    if(ch=='-') flag=1,ch=getchar();
    while (isdigit(ch)){x=x*10+(ch-'0'),ch=getchar();}
    x=flag?-x:x;
}
const int MN=5e5+15,ML=25;
int q,tot,n,m,u,v,cnt,dfn[MN],low[MN],s[MN],top;
int dep[MN],fa[MN][35],siz[MN],son[MN];
vector<int> adj[MN],t[MN];
void tarjan(int u){
    low[u]=dfn[u]=++tot;
    s[++top]=u;
    for(auto v:adj[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]==dfn[u]){
                cnt++;
                int p;
                t[cnt].push_back(u);
                t[u].push_back(cnt);
                do
                {
                    p=s[top--];
                    t[cnt].push_back(p);
                    t[p].push_back(cnt);
                } while (p!=v);
            }
        }else low[u]=min(low[u],dfn[v]);
    }
}
int cntt=0;
void dfs(int u,int pre){
    cntt++;
    // cout<<"U:"<<u<<" PRE:"<<pre<<'\n';
    dep[u]=dep[pre]+1;
    fa[u][0]=pre;
    for(int i=1;i<=ML;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(auto v:t[u]){
        if(v!=pre){
            dfs(v,u);
        }
    }
}
int lca(int x,int y){
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    for(int i=ML;i>=0;i--){
        if(dep[fa[y][i]]>=dep[x]){
            y=fa[y][i];
        }
    }
    if(x==y) return x;
    for(int i=__lg(dep[x]);i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
int main(){
    read(n);
    read(m);
    for(int i=1;i<=m;i++){
        int u,v;
        read(u);
        read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cnt=n;
    tarjan(1);
    dep[1]=1;
    // for(int i=n+1;i<=cnt;i++){
    //     for(auto v:t[i]){
    //         cout<<i<<" "<<v<<'\n';
    //     }
    // }
    // for(auto v:t[2]){
    //     cout<<v<<'\n';
    // }
    dfs(1,0);
    read(q);
    while (q--)
    {
        int u,v;
        read(u);
        read(v);
        //cout<<dep[u]<<" "<<dep[v]<<" "<<dep[lca(u,v)]<<'\n';
        // cout<<"LCA:"<<lca(u,v)<<'\n';
        cout<<((dep[u]+dep[v]-2*(dep[lca(u,v)]))>>1)+1<<'\n';
    }
    
    return 0;
}