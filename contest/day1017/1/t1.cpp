#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e5+15;
constexpr ll INF=1e18;
int n,m,sumq,ansx,ansy,x[MN],y[MN],midx,midy;
ll ans=INF,z;

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

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,cnt;
        ll sum;
    }t[MN<<2];

    void pushup(int p){
        t[p].sum=t[ls].sum+t[rs].sum;
        t[p].cnt=t[ls].cnt+t[rs].cnt;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].sum=t[p].cnt=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].cnt+=k;
            t[p].sum=1ll*t[p].l*t[p].cnt;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }
    
    int querycnt(int p,int fl,int fr){
        if(fl>fr) return 0;
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].cnt;
        }
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret+=querycnt(ls,fl,fr);
        if(mid<fr) ret+=querycnt(rs,fl,fr);
        return ret;
    }

    ll querysum(int p,int fl,int fr){
        if(fl>fr) return 0;
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].sum;
        }
        int mid=(t[p].l+t[p].r)>>1;
        ll ret=0;
        if(mid>=fl) ret+=querysum(ls,fl,fr);
        if(mid<fr) ret+=querysum(rs,fl,fr);
        return ret;
    }
}sgx,sgy;

ll calc(int x,int y){
    ll ret=0;

    auto xcnt1=sgx.querycnt(1,1,x);
    auto xcnt2=sgx.querycnt(1,x+1,n);
    auto xsum1=sgx.querysum(1,1,x);
    auto xsum2=sgx.querysum(1,x+1,n);
    ret+=((ll)x*xcnt1-xsum1)*z;
    ret+=(xsum2-(ll)x*xcnt2)*z;

    auto ycnt1=sgy.querycnt(1,1,y);
    auto ycnt2=sgy.querycnt(1,y+1,n);
    auto ysum1=sgy.querysum(1,1,y);
    auto ysum2=sgy.querysum(1,y+1,n);
    ret+=((ll)y*ycnt1-ysum1)*z;
    ret+=(ysum2-(ll)y*ycnt2)*z;

    return ret;
}

void solve(int x,int y){
    auto qwq=calc(x,y);
    if(qwq<ans){
        ans=qwq;
        ansx=x,ansy=y;
    }else if(qwq==ans){
        ansx=min(ansx,x);
        ansy=min(ansy,y);
    }
}

signed main(){
    read(n,m,z);
    sgx.build(1,1,n);
    sgy.build(1,1,n);
    for(int i=1;i<=m;i++){
        int q;
        read(x[i],y[i],q);
        sumq+=q;
        sgx.modify(1,x[i],1);
        sgy.modify(1,y[i],1);
    }

    sort(x+1,x+1+m);
    sort(y+1,y+1+m);
    midx=x[m>>1];   
    midy=y[m>>1];   
    for(int i=-300;i<=300;i++){
        for(int j=-300;j<=300;j++){
            int nx=midx+i,ny=midy+j;
            if(nx>=1&&nx<=n&&ny>=1&&ny<=n){
                solve(nx,ny);
            }
        }
    }
    put(ans+sumq);
    put(ansx,0);
    put(ansy);
    return 0;
}