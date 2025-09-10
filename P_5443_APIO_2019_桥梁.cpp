#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int u,v,w,id;
}e[MN];
struct Query{
    int op,x,y,id;
}qry[MN],q1[MN],q2[MN];
int n,m,blen,q,ans[MN],qtot,q1tot,q2tot,bel[MN],val[MN];
bool vis[MN];

struct DSU{
    struct Node{int x,y;}s[MN];
    int top,fa[MN],siz[MN];

    void init(){
        top=0;
        for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
    }

    int root(int x){return fa[x]==x?x:root(fa[x]);}

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        if(siz[rx]<siz[ry]) swap(rx,ry);
        s[++top]={rx,ry};
        fa[ry]=rx; siz[rx]+=siz[ry];
    }

    void rollback(int num){
        while(top>num){
            auto p=s[top--];
            fa[p.y]=p.y;
            siz[p.x]-=siz[p.y];
        }
    }
}dsu;

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

bool cmpe(Edge x,Edge y){return x.w>y.w;}
bool cmpq(Query x,Query y){return x.y>y.y;}


void init(){
    dsu.init();
    sort(e+1,e+1+m,cmpe);
    q1tot=q2tot=0;
    for(int i=1;i<=m;i++) vis[i]=0,val[i]=0,bel[e[i].id]=i;
    for(int i=1;i<=qtot;i++){
        if(qry[i].op==1){
            q1[++q1tot]=qry[i];
            vis[qry[i].x]=1;
        }else q2[++q2tot]=qry[i];
    }
    sort(q2+1,q2+q2tot+1,cmpq);
}

void solve(){
    init();
    int now,pos=1;
    for(int i=1;i<=q2tot;i++){
        auto p=q2[i];
        while(pos<=m && e[pos].w>=p.y){
            if(!vis[e[pos].id]) dsu.merge(e[pos].u,e[pos].v);
            pos++;
        }
        now=dsu.top;
        for(int j=1;j<=q1tot;j++) val[q1[j].x]=e[bel[q1[j].x]].w;
        for(int j=1;j<=q1tot;j++) if(q1[j].id<p.id) val[q1[j].x]=q1[j].y;
        for(int j=1;j<=q1tot;j++) if(val[q1[j].x]>=p.y) dsu.merge(e[bel[q1[j].x]].u,e[bel[q1[j].x]].v);
        ans[p.id]=dsu.siz[dsu.root(p.x)];
        dsu.rollback(now);
    }
    for(int i=1;i<=q1tot;i++) e[bel[q1[i].x]].w=q1[i].y;
}

signed main(){
    read(n,m);
    blen=sqrt(m*__lg(m));
    for(int i=1;i<=m;i++) read(e[i].u,e[i].v,e[i].w),e[i].id=i;
    read(q);
    for(int i=1;i<=q;i++){
        qry[++qtot].id=i;
        read(qry[qtot].op,qry[qtot].x,qry[qtot].y);
        if(qtot==blen) solve(),qtot=0;
    }
    if(qtot) solve();
    for(int i=1;i<=q;i++) if(ans[i]) put(ans[i]);
    return 0;
}
