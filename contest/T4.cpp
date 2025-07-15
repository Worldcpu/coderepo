#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,q,a[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct QWQ{
        int pos[11];
        
        QWQ operator +(const QWQ &x)const{
            QWQ ret;
            for(int i=1;i<=m+1;i++){
                ret.pos[i]=pos[x.pos[i]];
            }
            return ret;
        }
    };

    struct Node{
        int l,r;
        int isrev;
        QWQ val[2];
    }t[MN<<2];

    void dorev(int p){
        swap(t[p].val[1],t[p].val[0]);
        t[p].isrev^=1;
    }

    void pushdown(int p){
        if(t[p].isrev){
            dorev(ls);
            dorev(rs);
            t[p].isrev=0;
        }
    }

    void pushup(int p){
        t[p].val[0]=t[ls].val[0]+t[rs].val[0];
        t[p].val[1]=t[ls].val[1]+t[rs].val[1];
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            if(a[l]==1){
                t[p].val[0].pos[m+1]=m+1;
                t[p].val[1].pos[m+1]=1;
            }else{
                t[p].val[0].pos[m+1]=1;
                t[p].val[1].pos[m+1]=m+1;
            }
            for(int i=1;i<=m;i++){
                t[p].val[0].pos[i]=t[p].val[1].pos[i]=i+1;
            }
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            dorev(p);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr);
        if(mid<fr) modify(rs,fl,fr);
        pushup(p);
    }

    QWQ query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val[0];
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr);
        if(mid>=fr) return query(ls,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
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

signed main(){
    freopen("boyi.in","r",stdin);
    freopen("boyi.out","w",stdout);
    read(n,m,q);
    for(int i=1;i<=n;i++){
        read(a[i]);
        a[i]=(a[i]&1)^1;
    }
    sg.build(1,1,n);
    while(q--){
        int op,l,r,x;
        read(op,l,r);
        if(op==1){
            read(x);
            if(x&1) sg.modify(1,l,r);
        }else{
            auto ret=sg.query(1,l,r);
            if(ret.pos[m+1]==1){
                put("Bob");
            }else put("Alice");
        }
    }
    return 0;
}

