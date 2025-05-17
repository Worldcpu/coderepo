#include<bits/stdc++.h>
#define ll int
using namespace std;
constexpr int MN=5e6+15;
ll n,m,w[MN],b[MN];
vector<int> adj[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        ll l,r,val,add;
    }t[MN<<2];


    void pushdown(int p){
        if(t[p].add){
            t[ls].add+=t[p].add;
            t[rs].add+=t[p].add;
            t[ls].val+=t[p].add;
            t[rs].val+=t[p].add;
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=w[b[l]];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modify(int p,int fl,int fr,ll k){
        if(t[p].l>=fl&&t[p].r<=fr){
            t[p].val+=k;
            t[p].add+=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
    }

    ll query(int p,int pos){
        if(t[p].l==t[p].r){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return query(ls,pos);
        else return query(rs,pos);
    }

#undef ls
#undef rs
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

namespace FHQTreap{
struct FHQ{
    vector <int> s;
    inline void insert(int x){
        s.insert(lower_bound(s.begin(),s.end(),x),x);
    }
    inline void del(int x){
        s.erase(lower_bound(s.begin(),s.end(),x));
    }
    inline int topk(int p,int k){
        return s[k-1];
    }
}fhq[MN];
}
namespace fhq=FHQTreap;

namespace Tree{
    int tot,id[MN],fa[MN],siz[MN],top[MN],hson[MN],dep[MN];

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

    void dfs2(int u,int ltop){
        top[u]=ltop;
        id[u]=++tot;
        b[tot]=u;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
            fhq::fhq[u].insert(w[v]);
        }
    }

    void modify(int x,int y,int z){
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            if(fa[top[x]]){
                ll s=sg.query(1,id[top[x]]);
                fhq::fhq[fa[top[x]]].del(s);
                fhq::fhq[fa[top[x]]].insert(s+z);
            }        
            sg.modify(1,id[top[x]],id[x],z);
            x=fa[top[x]];
        }
        if(dep[x]<dep[y]) swap(x,y);
        if(top[y]==y&&fa[y]){
            ll s=sg.query(1,id[y]);
            fhq::fhq[fa[top[y]]].del(s);
            fhq::fhq[fa[top[y]]].insert(s+z);
        }
        sg.modify(1,id[y],id[x],z);
    }
}
namespace t=Tree;

int main(){
    read(n),read(m);
    for(int i=1;i<=n;i++){
        read(w[i]);
    }
    for(int i=1;i<n;i++){
        int u,v;
        read(u);
        read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    t::dfs1(1,0);
    t::dfs2(1,1);
    sg.build(1,1,n);
    while(m--){
        int op,x,y,z;
        read(op);
        read(x);
        read(y);
        if(op==1){
            read(z);
            t::modify(x,y,z);
        }else{
            int qf,qhs,qx;
            if(t::fa[x]){
                qf=sg.query(1,t::id[t::fa[x]]);
                fhq::fhq[x].insert(qf);
            }
            if(t::hson[x]){
                qhs=sg.query(1,t::id[t::hson[x]]);
                fhq::fhq[x].insert(qhs);
            }
            qx=sg.query(1,t::id[x]);
            fhq::fhq[x].insert(qx);
            put(fhq::fhq[x].topk(114514,y));
            if(t::fa[x]) fhq::fhq[x].del(qf);
            if(t::hson[x]) fhq::fhq[x].del(qhs);
            fhq::fhq[x].del(qx);
        }
    }
    return 0;
}
