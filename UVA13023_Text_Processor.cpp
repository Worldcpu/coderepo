#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,K,ans[MN],pos[MN];
string s;
vector<int> adj[MN];
vector<pir> qry[MN];

struct BIT{
    int t1[MN],t2[MN];
    
    void clear(){
        memset(t1,0,sizeof(t1));
        memset(t2,0,sizeof(t2));
    }

    int lowbit(int x){return x&-x;}

    void modify(int x,int k){
        int tmp=x;
        while(x<MN){
            t1[x]+=k;
            t2[x]+=tmp*k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        int tmp=x;
        while(x){
            ret+=t1[x]*(tmp+1)-t2[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int query(int l,int r){
        return query(r)-query(l-1);
    }

    void update(int l,int r,int k){
        modify(l,k);
        modify(r+1,-k);
    }

}bit;

namespace SAM{// 1-based
    int nxt[MN][26],len[MN],fa[MN],tot,lst;

    void initsam(){
        for(int i=0;i<=tot;i++){
            adj[i].clear();
            fa[i]=len[i]=pos[i]=0;
            memset(nxt[i],0,sizeof(nxt[i]));
        }
        tot=lst=1;
    }

    inline void expand(int c,int id){
        int cur=++tot;
        len[cur]=len[lst]+1;
        pos[id]=cur;
        int p=lst;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int nq=++tot;
                len[nq]=len[p]+1,fa[nq]=fa[q];
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[q]=fa[cur]=nq;
                while(nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }

    inline void inittree(){
        for(int i=2;i<=tot;i++) adj[fa[i]].push_back(i);
    }

}using namespace SAM;

namespace Tree{
    struct Kuai{
        int l,r,v;
    };
    int dfn[MN],htop[MN],hson[MN],siz[MN],dep[MN],id[MN],dtot;
    vector<Kuai> odt[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(!hson[u]||siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        dfn[u]=++dtot;
        id[dtot]=u;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==hson[u]) continue;
            dfs2(v,v);
        }
    }
}using namespace Tree;

void init(){
    dtot=0;
    for(int i=0;i<=tot;i++){
        siz[i]=hson[i]=dep[i]=dfn[i]=htop[i]=ans[i]=pos[i]=id[i]=0;
        odt[i].clear();
    }
    for(int i=0;i<=n;i++){
        qry[i].clear();
        qry[i].shrink_to_fit();
    }
    initsam();
    bit.clear();
}

void update(int u,int x){
    bit.update(1,x,1);
    while(u){
        while(odt[htop[u]].size()){
            auto it=odt[htop[u]].back();
            odt[htop[u]].pop_back();
            if(it.r<=dfn[u]){
                int l=len[fa[id[it.l]]]+1,r=len[id[it.r]];
                bit.update(it.v-r+1,it.v-l+1,-1);
                if(it.r==dfn[u]) break;
            }else{
                int l=len[fa[id[it.l]]]+1,r=len[u];
                bit.update(it.v-r+1,it.v-l+1,-1);
                odt[htop[u]].push_back({dfn[u]+1,it.r,it.v});
                break;
            }
        }
        odt[htop[u]].push_back({dfn[htop[u]],dfn[u],x});
        u=fa[htop[u]];
    }
}

void solve(){
    init();
    cin>>m;
    n=s.length();
    s=" "+s;
    for(int i=1;i<=n;i++){
        expand(s[i]-'a',i);
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        qry[r].push_back(pir(l,i));
    }
    inittree();
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        update(pos[i],i);
        for(auto it:qry[i]){
            ans[it.second]=bit.query(it.first,i);
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
}

signed main(){
    while(cin>>s){
        solve();
    }

    return 0;
}
