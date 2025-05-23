#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9+7;
struct Query{
    int l,r,id;
};
int n,m,qtot,btot,ans[MN],a[MN],b[MN],pre[MN],lst[MN];
vector<Query> q;

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=min(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=INF;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=min(t[p].val,k);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) update(ls,pos,k);
        else update(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1,ret=INF;
        if(mid>=fl) ret=min(ret,query(ls,fl,fr));
        if(mid<fr) ret=min(ret,query(rs,fl,fr));
        return ret;
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

bool cmp(Query x,Query y){
    return x.r<y.r;
}

int main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        read(a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    btot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+btot,a[i])-b;
        pre[i]=lst[a[i]];
        lst[a[i]]=i;
    }
    sg.build(1,1,n);
    for(int i=1;i<=m;i++){
        int l,r;
        read(l,r);
        q.push_back({l,r,i});
    }
    sort(q.begin(),q.end(),cmp);
    int now=1;
    for(auto p:q){
        int l=p.l,r=p.r;
        while(now<=r){
            if(!pre[now]){
                now++;
                continue;
            }
            sg.update(1,pre[now],now-pre[now]);
            now++;
        }
        ans[p.id]=sg.query(1,l,r);
    }
    for(int i=1;i<=m;i++) put((ans[i]==INF?-1:ans[i]));
    return 0;
}
