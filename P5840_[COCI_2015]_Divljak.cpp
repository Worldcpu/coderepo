#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int n,q,a[MN];
vector<int> adj[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

}bit;

struct ACAuto{
    int t[MN][26],tot=1,fail[MN],end[MN];

    void insert(string s,int id){
        int p=1;
        for(auto c:s){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[id]=p;
    }

    void build(){
        queue<int> q;
        for(int i=0;i<26;i++){
            t[0][i]=1;
        }
        q.push(1);

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

}t;

namespace Tree{
    int dfn[MN],dfntot,fa[MN],dep[MN],siz[MN],hson[MN],htop[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int top){
        htop[u]=top;
        dfn[u]=++dfntot;
        if(!hson[u]) return;
        dfs2(hson[u],top);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]){
                swap(x,y);
            }
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

}using namespace Tree;

bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        t.insert(s,i);
    }
    t.build();
    for(int i=2;i<=t.tot;i++){
        cerr<<t.fail[i]<<" ";
        adj[t.fail[i]].push_back(i);
    }
    dfs1(1,0);
    dfs2(1,1);
    cin>>q;

    while(q--){
        int op,x;
        string p;
        cin>>op;
        if(op==1){
            cin>>p;
            int len=p.length(),u=1;
            p=" "+p;
            for(int i=1;i<=len;i++){
                int v=p[i]-'a';
                u=t.t[u][v];
                a[i]=u;
            }
            sort(a+1,a+1+len,cmp);
            for(int i=1;i<=len;i++){
                bit.modify(dfn[a[i]],1);
            }
            for(int i=1;i<len;i++){
                bit.modify(dfn[lca(a[i],a[i+1])],-1);
            }
        }else{
            cin>>x;
            int p=t.end[x];
            cout<<bit.query(dfn[p]+siz[p]-1)-bit.query(dfn[p]-1)<<'\n';
        }
    }
    return 0;
}
