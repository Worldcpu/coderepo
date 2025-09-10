#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=6e5+15,INF=1e9;
struct Edge{
    int u,v,w;
}e[MN];
int n,q,dtot,val[MN];
vector<int> adj[MN];

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
    int hson[MN],fa[MN],htop[MN],siz[MN],dep[MN],dfn[MN],id[MN],dftot;

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        siz[u]=1;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        dfn[u]=++dftot;
        id[dftot]=u;
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

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        pir mn,mx;
        
        Node(int a=INF,int b=-INF){
            mn=pir(a,-1),mx=pir(b,-1);
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.mn=x.mn.first<y.mn.first?x.mn:y.mn;
            ret.mx=x.mx.first>y.mx.first?x.mx:y.mx;
            return ret;
        }
    };

    struct SNode{
        int l,r,tag;// k=1 cov it back,k=2 cov it to all
        Node all,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].all=t[ls].all+t[rs].all;
        t[p].val=t[ls].val+t[rs].val;
    }

    void dochg(int p,int k){
        t[p].val=(k==1?Node():t[p].all);
        t[p].tag=k;
    }

    void pushdown(int p){
        if(t[p].tag){
            dochg(ls,t[p].tag);
            dochg(rs,t[p].tag);
            t[p].tag=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].all.mn=t[p].all.mx=pir(dfn[l],l);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            dochg(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    Node query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fr) return query(ls,fl,fr);
        if(mid<fl) return query(rs,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }

}sg;

namespace EXKru{
    int pre[MN];

    void initpre(){
        for(int i=0;i<MN;i++){
            pre[i]=i;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    bool cmp(Edge x,Edge y){
        return x.w<y.w;
    }

    void solve(){
        sort(e+1,e+n,cmp);
        dtot=n;
        for(int i=1;i<n;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru!=rv){
                dtot++;
                val[dtot]=e[i].w;
                pre[ru]=pre[rv]=dtot;
                adj[dtot].push_back(ru);
                adj[dtot].push_back(rv);
                if(dtot==2*n-1) break;
            }
        }

    }

}

int main(){
    EXKru::initpre();
    read(n,q);
    for(int i=1;i<n;i++){
        read(e[i].u,e[i].v,e[i].w);
    }
    EXKru::solve();
    dfs1(dtot,0);
    dfs2(dtot,dtot);
    sg.build(1,1,dtot);
    while(q--){
        int op,x,y;
        read(op,x);
        if(op==1){
            read(y);
            sg.modify(1,x,y,2);
        }
        if(op==2){
            read(y);
            sg.modify(1,x,y,1);
        }
        if(op==3){
            auto ret=sg.query(1,1,n);
            if(ret.mn.second==-1||ret.mx.second==-1||(ret.mx.second==ret.mn.second&&ret.mn.second==x)){
                put(-1);
            }else{
                put(max(val[lca(x,ret.mn.second)],val[lca(x,ret.mx.second)]));
            }
        }
    }
    return 0;
}