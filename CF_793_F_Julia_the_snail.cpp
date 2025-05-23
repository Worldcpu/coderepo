#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15,INF=1e9;
struct Line{
    int l,r;
}ln[MN];
struct Query{
    int x,y,id;
};
int n,m,q,ans[MN],lnl[MN];
vector<pir> qry[MN];

struct SegmentBeat{
#define ls p<<1
#define rs p<<1|1

    struct{
        int l,r,mx,se,tagp,tagk;  
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
        if(t[ls].mx==t[rs].mx){
            t[p].se=max(t[ls].se,t[rs].se);
        }
        else if(t[ls].mx>t[rs].mx){
            t[p].se=max(t[ls].se,t[rs].mx);
        }else{
            t[p].se=max(t[ls].mx,t[rs].se);
        }
    }

    void doit(int p,int pos,int k){
        if(t[p].mx>=pos){
            t[p].mx=k;
            if(!t[p].tagp) t[p].tagp=pos;
            t[p].tagk=k;
        }
    }

    void pushdown(int p){
        if(t[p].tagp){
            doit(ls,t[p].tagp,t[p].tagk);
            doit(rs,t[p].tagp,t[p].tagk);
            t[p].tagp=t[p].tagk=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mx=l;
            t[p].se=-INF;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }


    void modify(int p,int fl,int fr,int pos,int v){
        if(t[p].mx<pos||t[p].l>fr||t[p].r<fl) return;
        if(t[p].l>=fl&&t[p].r<=fr&&t[p].se<pos){
            doit(p,pos,v);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        modify(ls,fl,fr,pos,v);
        modify(rs,fl,fr,pos,v);
        pushup(p);
    }

    int query(int p,int pos){
        if(t[p].l==t[p].r){
            return t[p].mx;
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

void solve(){
    for(int i=1;i<=n;i++){
        if(lnl[i]) sg.modify(1,1,lnl[i],lnl[i],i);
        for(auto p:qry[i]) ans[p.second]=sg.query(1,p.first);
    }
}

int main(){
    memset(ans,0x3f,sizeof(ans));
    read(n,m);
    sg.build(1,1,n);
    for(int i=1;i<=m;i++){
        int l,r;
        read(l,r);
        lnl[r]=l;
    }
    read(q);
    for(int i=1;i<=q;i++){
        int x,y;
        read(x,y);
        qry[y].push_back(pir(x,i));
    }
    solve();
    for(int i=1;i<=q;i++){
        put(ans[i]);
    }
    return 0;
}
