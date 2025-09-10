#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int a[MN],ctot,n,m;
vector<int> adj[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int lv,rv,sum;
        
        Node(int x=0,int y=0,int z=0){
            lv=x,rv=y,sum=z;
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.lv=x.lv,ret.rv=y.rv;
            ret.sum=x.sum+y.sum+(x.rv==y.lv);
            return ret;
        }

    };
    struct SNode{
        int l,r,cov;
        Node val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void docov(int p,int k){
        t[p].val={k,k,t[p].r-t[p].l};
        t[p].cov=k;
    }

    void pushdown(int p){
        if(t[p].cov){
            docov(ls,t[p].cov);
            docov(rs,t[p].cov);
            t[p].cov=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].cov=0;
        if(l==r){
            t[p].val=Node(a[l],a[l],0);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            docov(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    auto query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        int ret=0;
        if(mid>=fr) return query(ls,fl,fr);
        if(mid<fl) return query(rs,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }

    int queryv(int p,int pos){
        if(t[p].l==t[p].r){
            return t[p].val.lv;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return queryv(ls,pos);
        else return queryv(rs,pos);
    }

}sg;

namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
            inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            template<typename type>inline void write(type *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch;read(ch),x.clear();do x+=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const string &x){for(int i=0,len=x.length();i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
            template<typename type>
            inline void put(const type &x,bool flag=1){write(x),flag?putchar('\n'):putchar(' ');}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;

namespace Tree{
    int dep[MN],hson[MN],htop[MN],siz[MN],dfn[MN],id[MN],fa[MN],dtot;

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
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
        dfn[u]=++dtot;
        id[dtot]=u;
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

    void modify(int x,int y,int k){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            sg.modify(1,dfn[htop[x]],dfn[x],k);
            x=fa[htop[x]];
        }
        if(dep[x]>dep[y]) swap(x,y);
        sg.modify(1,dfn[x],dfn[y],k);
    }

    int query(int x,int y){
        int ret=0;
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            ret+=sg.query(1,dfn[htop[x]],dfn[x]).sum;
            if(sg.queryv(1,dfn[fa[htop[x]]])==sg.queryv(1,dfn[htop[x]])) ret++;
            x=fa[htop[x]];
        }
        if(dep[x]>dep[y]) swap(x,y);
        ret+=sg.query(1,dfn[x],dfn[y]).sum;
        return ret;
    }

}using namespace Tree;

void init(){
    ctot=dtot=0;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        siz[i]=hson[i]=htop[i]=dep[i]=fa[i]=dfn[i]=id[i]=0;
        a[i]=0;
    }
}

void solve(){
    read(n,m);
    init();
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        a[i]=i;
    }
    ctot=n;
    dfs1(1,0);
    dfs2(1,1);
    sg.build(1,1,n);   
    while(m--){
        int op,x,y;
        read(op,x,y);
        if(op==1){
            modify(x,y,++ctot);
        }else{
            put(query(x,y));
        }
    }
}

signed main(){
    int T;
    read(T);
    while(T--){
        solve();
    }
    return 0;
}