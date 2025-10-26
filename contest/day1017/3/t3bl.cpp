#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=1e9,ML=30;
int n,q,dg[MN],mxdg;
bool vis[MN];
vector<int> adj[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1

    struct Node{
        int mn,mnid;

        Node(int mnn=INF,int mnidd=0){
            mn=mnn,mnid=mnidd;
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.mn=min(x.mn,y.mn);
            if(ret.mn==x.mn) ret.mnid=x.mnid;
            else ret.mnid=y.mnid;
            return ret;
        }

    };

    struct SNode{
        int l,r;
        Node val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=Node(INF,l);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val.mn=k;;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

}sg;

namespace Tree{
    int dfn[MN],siz[MN],dep[MN],fa[MN],htop[MN],hson[MN],rt,tot;

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        dfn[u]=++tot;
        siz[u]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
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

namespace Sub1{
    set<int> black;

void solve(){
    dfs1(1,0);
    dfs2(1,1);
    while(q--){
        int x;
        cin>>x;
        if(x>0){
            if(vis[x]){
                vis[x]=0;
                black.erase(x);
            }
            else{
                vis[x]=1;
                black.insert(x);           
            }
        }else{
            x=-x;
            if(black.empty()){
                cout<<0<<'\n';
            }else{
                int mxdep=-INF,mxid=x;
                for(auto p:black){
                    int qlca=lca(p,x);
                    if(dep[qlca]>mxdep){
                        mxdep=dep[qlca];
                        mxid=qlca;
                    }
                }
                cout<<mxid<<'\n';
            }
        }
    }
}
}

namespace Sub2{
    int btot;

    void solve(int rt){
        cerr<<rt<<'\n';
        dfs1(rt,0);
        sg.build(1,1,n);
        while(q--){
            int x;
            cin>>x;
            if(x>0){
                if(vis[x]){
                    sg.modify(1,x,INF);
                    vis[x]=0;
                    btot--;
                }else{
                    sg.modify(1,x,dep[x]);
                    vis[x]=1;
                    btot++;
                }            
            }else{
                x=-x;
                if(!btot){
                    cout<<0<<'\n';
                    continue;
                }
                if(dep[x]>sg.t[1].val.mn){
                    cout<<sg.t[1].val.mnid<<'\n';
                }else{
                    cout<<x<<'\n';
                }
            }
            cerr<<x<<' '<<sg.t[1].val.mn<<' '<<sg.t[1].val.mnid<<'\n';
        }
    }
}


int main(){
    cin>>n>>q;

    int mndg=INF,mnid=0;
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa;
        adj[fa].push_back(i);
        adj[i].push_back(fa);
        dg[fa]++;
        dg[i]++;
        mxdg=max({mxdg,dg[fa],dg[i]});
    }
    for(int i=1;i<=n;i++){
        if(mndg>dg[i]){
            mndg=dg[i];
            mnid=i;
        }
    }
        Sub1::solve();
    return 0;
}