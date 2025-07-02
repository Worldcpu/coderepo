#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+1145;
int n,m,pval[MN];
vector<int> adj[MN];
multiset<int> val[MN];

struct ACAuto{
    int t[MN][26],tot,fail[MN],end[MN];

    void insert(string s,int x){
        int p=0;
        for(auto c:s){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[x]=p;
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
        for(int i=1;i<=tot;i++){
            adj[fail[i]].push_back(i); 
        }
    }

}ac;

struct Segment{
#define ls p<<1
#define rs p<<1|1


    struct Node{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=max(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=-1;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1;
        int ret=-1;
        if(mid>=fl) ret=max(ret,query(ls,fl,fr));
        if(mid<fr) ret=max(ret,query(rs,fl,fr));
        return ret;
    }

#undef ls 
#undef rs
}sg;

namespace Tree{
    int id[MN],dtot,siz[MN],dep[MN],fa[MN],hson[MN],htop[MN];

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        siz[u]=1;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(!hson[u]||siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int top){
        htop[u]=top;
        id[u]=++dtot;
        if(!hson[u]) return;
        dfs2(hson[u],top);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int querychain(int x,int y){
        int ret=-1;
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            ret=max(ret,sg.query(1,id[htop[x]],id[x]));
            x=fa[htop[x]];
        }
        if(dep[x]>dep[y]) swap(x,y);
        ret=max(ret,sg.query(1,id[x],id[y]));
        return ret;
    }

}
using namespace Tree;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        ac.insert(s,i);
    }
    ac.build();
    sg.build(1,1,MN-1);
    dfs1(0,0);
    dfs2(0,0);
    for(int i=1;i<=n;i++){
        sg.modify(1,id[ac.end[i]],0);
        pval[i]=0;
         val[ac.end[i]].insert(0);
    }

    for(int i=1;i<=m;i++){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            cin>>x>>y;
            val[ac.end[x]].erase(val[ac.end[x]].find(pval[x]));
            pval[x]=y;
            val[ac.end[x]].insert(pval[x]);
            sg.modify(1,id[ac.end[x]],*prev(val[ac.end[x]].end()));
        }else{
            string s;
            cin>>s;
            int p=0,ret=-1;
            for(auto c:s){
                int k=c-'a';
                p=ac.t[p][k];
                ret=max(ret,querychain(0,p));
            }
            cout<<ret<<'\n';
        }
    }

    return 0;
}
