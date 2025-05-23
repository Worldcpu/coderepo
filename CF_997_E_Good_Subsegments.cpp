#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1.2*1e5+15;
int n,q,top1,top2,ans[MN],a[MN],s1[MN],s2[MN];
vector<pir> qry[MN];

struct Segment {
#define ls p<<1
#define rs p<<1|1
#define INF 1e9
    
    struct{
        int l,r,minn,tagcnt,mncnt,tagadd,ans;
    }t[MN<<2];

    void pushup(int p){
        t[p].minn=min(t[ls].minn,t[rs].minn);
        t[p].mncnt=0;
        if(t[p].minn==t[ls].minn) t[p].mncnt+=t[ls].mncnt;
        if(t[p].minn==t[rs].minn) t[p].mncnt+=t[rs].mncnt;
        t[p].ans=t[ls].ans+t[rs].ans;
    }

    void doadd(int p,int k){
        t[p].tagadd+=k;
        t[p].minn+=k;
    }

    void docnt(int p,int k){
        t[p].ans+=t[p].mncnt*k;
        t[p].tagcnt+=k;
    }

    void pushdown(int p){
        if(t[p].tagadd){
            doadd(ls,t[p].tagadd);
            doadd(rs,t[p].tagadd);
            t[p].tagadd=0;
        }
        if(t[p].tagcnt){
            docnt(ls,t[p].minn==t[ls].minn?t[p].tagcnt:0);
            docnt(rs,t[p].minn==t[rs].minn?t[p].tagcnt:0);
            t[p].tagcnt=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].minn=l;
        t[p].mncnt=1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) update(ls,fl,fr,k);
        if(mid<fr) update(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].ans;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=query(ls,fl,fr);
        if(mid<fr) ret+=query(rs,fl,fr);
        return ret;
    }

#undef ls
#undef rs
#undef INF
} sg;

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
    read(n);
    for(int i=1;i<=n;i++) read(a[i]);
    read(q);
    for(int i=1;i<=q;i++){
        int l,r;
        read(l,r);
        qry[r].push_back(pir(l,i));
    }
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        sg.doadd(1,-1);
        while(top1&&a[i]>a[s1[top1]]){
            sg.update(1,s1[top1-1]+1,s1[top1],a[i]-a[s1[top1]]);
            top1--;
        }
        s1[++top1]=i;
        while(top2&&a[i]<a[s2[top2]]){
            sg.update(1,s2[top2-1]+1,s2[top2],a[s2[top2]]-a[i]);
            top2--;
        }
        s2[++top2]=i;
        sg.docnt(1,1);
        for(auto p:qry[i]){
            ans[p.second]=sg.query(1,p.first,i);
        }
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
    return 0;
}
