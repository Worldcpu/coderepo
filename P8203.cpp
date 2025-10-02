#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,q;
string s[MN],t[MN];
vector<int> adj[MN];

struct ACAuto{
    int t[MN][26],end[MN],fail[MN],tot;

    void insert(string st,int id){
        int p=0;
        for(auto c:st){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[p]++;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            if(t[0][i]) q.push(t[0][i]);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                int v=t[u][i];
                if(v){
                    fail[v]=t[fail[u]][i];
                    q.push(v);
                }else t[u][i]=t[fail[u]][i];
            }
        }
    }
}ac;

namespace Tree{
    int dfn[MN],hson[MN],siz[MN],dep[MN],htop[MN],dtot,fa[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        siz[u]=1;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        dfn[u]=++dtot;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) return;
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
}using namespace Tree;

int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        cin>>s[i];
        ac.insert(s[i],i);
    }
    for(int i=1;i<=m;i++){
        cin>>t[i];
    }
    for(int i=1;i<=q;i++){

    }

    return 0;
}