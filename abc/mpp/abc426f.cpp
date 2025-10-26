#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MN = 500000 + 15;
int n,q;
ll a[MN];


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
        int l,r;
        ll sum;
        int mx,mn; 
        ll add;   
        bool set0; 
    } t[MN<<2];

    void pushup(int p){
        t[p].sum = t[ls].sum + t[rs].sum;
        t[p].mx = max(t[ls].mx, t[rs].mx);
        t[p].mn = min(t[ls].mn, t[rs].mn);
    }

    void doclr(int p){
        t[p].sum = 0;
        t[p].mx = t[p].mn = 0;
        t[p].add = 0;
        t[p].set0 = true;
    }

    void doadd(int p, ll k){ 
        t[p].sum += (t[p].r - t[p].l + 1) * k;
        t[p].mx = int(t[p].mx + k);
        t[p].mn = int(t[p].mn + k);
        t[p].add += k;
    }

    void pushdown(int p){
        if(t[p].set0){
            doclr(ls);
            doclr(rs);
        }
        if(t[p].add != 0){
            doadd(ls, t[p].add);
            doadd(rs, t[p].add);
            t[p].add = 0;
        }
    }

    void build(int p,int l,int r){
        t[p].l = l; t[p].r = r;
        t[p].add = 0; t[p].set0 = false;
        if(l==r){
            t[p].sum = a[l];
            t[p].mx = t[p].mn = int(a[l]);
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>fr || t[p].r<fl) return;
        if(t[p].set0) return;
        if(fl<=t[p].l && t[p].r<=fr){
            if(t[p].mx <= k){
                doclr(p);
                return;
            }
            if(t[p].mn > k){
                doadd(p, - (ll)k);
                return;
            }
        }
        pushdown(p);
        modify(ls,fl,fr,k);
        modify(rs,fl,fr,k);
        pushup(p);
    }

    ll query(int p,int fl,int fr,int k){
        if(t[p].l>fr || t[p].r<fl) return 0;
        if(t[p].set0) return 0;
        if(fl<=t[p].l && t[p].r<=fr){
            if(t[p].mx <= k) return t[p].sum; 
            if(t[p].mn > k) return (ll)(t[p].r - t[p].l + 1) * k; 
        }
        pushdown(p);
        return query(ls,fl,fr,k) + query(rs,fl,fr,k);
    }
} sg;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    read(n);
    for(int i=1;i<=n;i++) read(a[i]);
    sg.build(1,1,n);
    read(q);
    while(q--){
        int l,r,k;
        read(l,r,k);
        put(sg.query(1,l,r,k));
        sg.modify(1,l,r,k);
    }
    return 0;
}
