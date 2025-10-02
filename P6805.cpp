#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int fq[MN],dg[MN],n,q,lftot,a[MN];
vector<int> adj[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,sum1,rev;
    }t[MN<<2];

    void pushup(int p){
        t[p].sum1=t[ls].sum1+t[rs].sum1;
    }

    void dorev(int p){
        t[p].rev^=1;
        t[p].sum1=(t[p].r-t[p].l+1)-t[p].sum1;
    }

    void pushdown(int p){
        if(t[p].rev){
            dorev(ls);
            dorev(rs);
            t[p].rev=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void rev(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            dorev(p);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) rev(ls,fl,fr);
        if(mid<fr) rev(rs,fl,fr);
        pushup(p);
    }

    int query0(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return (t[p].r-t[p].l+1)-t[p].sum1;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=query0(ls,fl,fr);
        if(mid<fr) ret+=query0(rs,fl,fr);
        return ret;
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
    int hson[MN],htop[MN],fa[MN],siz[MN],dep[MN],dfn[MN],id[MN],dtot,rt;

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

    void changeroute(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            sg.rev(1,dfn[htop[x]],dfn[x]);
            x=fa[htop[x]];
        }
        if(dep[x]>dep[y]) swap(x,y);
        sg.rev(1,dfn[x],dfn[y]);
    }

}using namespace Tree;

signed main(){
    read(n,q);
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        dg[u]++;
        dg[v]++;
    }
    for(int i=1;i<=n;i++){
        if(dg[i]>=2){
            rt=i;
            break;           
        }
    }
    dfs1(rt,0);
    dfs2(rt,rt);
    sg.build(1,1,dtot);
    for(int i=1;i<=n;i++){
        if(dg[i]==1){
            lftot++;
            changeroute(i,rt);
        }
    }
    while(q--){
        int d,tot=lftot;
        read(d);
        for(int i=1;i<=d;i++){
            read(a[i]);
            if(dg[a[i]]!=1){
                tot++;
                changeroute(a[i],rt);
            }
            dg[a[i]]++;
        }
        if(tot&1){
            put(-1);
        }else{
            put(n+d-2+sg.query0(1,1,dtot));
        }
        for(int i=1;i<=d;i++){
            dg[a[i]]--;
            if(dg[a[i]]!=1){
                changeroute(a[i],rt);
            }
        }
    }
    

    return 0;
}