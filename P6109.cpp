#include <bits/stdc++.h>
#define int long long // IF TLE Don't Forget This!
using namespace std;
constexpr int BASEN = 1<<16; 
constexpr int MN = BASEN + 20,MQ=5e5+15; 
const long long BIG = 180000000000000LL;
const long long NEG_INF = -(1LL<<60);

struct Query{
    int l1,r1,l2,r2,id;
}qry[MQ];
int n,m,q,ans[MQ];

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

namespace EWSegment{
    struct Line{
        int l,r,k;
    };
    vector<Line> ln[MN],ql[MN],qr[MN];
    vector<int> T[19];

    struct FirstSegment{
        #undef ls
        #undef rs
        #define ls (p<<1)
        #define rs (p<<1|1)
        struct segtree
        {
            int l, r;
            int ans, hans;
            int sum, mxsum;
            bool hclr;
        } t[4 * MN];

        void pushup(int p)
        {
            t[p].ans = max(t[ls].ans, t[rs].ans);
            t[p].hans = max(t[ls].hans, t[rs].hans);
        }

        void dosum(int p, int k, int maxk)
        {
                t[p].mxsum = max(t[p].mxsum, t[p].sum + maxk);
                t[p].hans = max(t[p].hans, t[p].ans + maxk);
                t[p].ans += k;
                t[p].sum += k;
        }

        void doclr(int p){
            dosum(ls,t[p].sum,t[p].mxsum);
            dosum(rs,t[p].sum,t[p].mxsum);
            t[p].hclr=1;
            t[p].mxsum=t[p].sum=0;
            t[p].hans=t[p].ans;
        }

        void pushdown(int p)
        {
            if(t[p].hclr){
                doclr(ls);
                doclr(rs);
                t[p].hclr=0;
            }
            if(t[p].sum || t[p].mxsum){
                dosum(ls, t[p].sum, t[p].mxsum);
                dosum(rs, t[p].sum, t[p].mxsum);
                t[p].sum = t[p].mxsum = 0;
            }
        }

        void build(int p, int l, int r)
        {
            t[p].l = l;
            t[p].r = r;
            t[p].ans = t[p].hans = 0;
            t[p].sum = t[p].mxsum = 0;
            t[p].hclr = 0;
            if (l == r)
            {
                t[p].hans = t[p].ans =0;
                return;
            }
            int mid = (l + r) >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            pushup(p);
        }

        int query(int p, int fl, int fr)
        {
            if (t[p].l >= fl && t[p].r <= fr)
            {
                return t[p].ans;
            }
            pushdown(p);
            int mid = (t[p].l + t[p].r) >> 1;
            int res = (int)NEG_INF;
            if (mid >= fl)
            {
                res = query(ls, fl, fr);
            }
            if (mid < fr)
            {
                res = max(res, query(rs, fl, fr));
            }
            return res;
        }

        int queryhis(int p, int fl, int fr)
        {
            if (t[p].l >= fl && t[p].r <= fr)
            {
                nth_element
                return t[p].hans;
            }
            pushdown(p);
            int mid = (t[p].l + t[p].r) >> 1;
            int res = (int)NEG_INF;
            if (mid >= fl)
            {
                res = queryhis(ls, fl, fr);
            }
            if (mid < fr)
            {
                res = max(res, queryhis(rs, fl, fr));
            }
            return res;
        }

        void add(int p, int fl, int fr, int k)
        {
            if (t[p].l >= fl && t[p].r <= fr)
            {
                dosum(p, k, k);
                return;
            }
            pushdown(p);
            int mid = (t[p].l + t[p].r) >> 1;
            if (mid >= fl)
            {
                add(ls, fl, fr, k);
            }
            if (mid < fr)
            {
                add(rs, fl, fr, k);
            }
            pushup(p);
        }
    }fsg;
    #undef ls
    #undef rs

    #define ls (t[p].l+t[p].r)
    #define rs (ls^1)

    struct Node{
        int l,r,fa;
        vector<int> ln;
    }t[MN<<2];

    void build(int p,int l,int r,int lp){
        t[p].l=l;
        t[p].r=r;
        T[lp].push_back(p);
        if(l==r) return;
        int mid=(l+r)>>1;
        t[p<<1].fa = t[p<<1|1].fa = p;
        build(p<<1,l,mid,lp+1);
        build(p<<1|1,mid+1,r,lp+1);
    }

    void push(int p,int fl,int fr,int id){
        int mid=(t[p].l + t[p].r)>>1;
        if((fl <= mid && mid < fr) || t[p].r - t[p].l == 1){
            t[p].ln.push_back(id);
            return;
        }
        if(fr <= mid) push(p<<1,fl,fr,id);
        else if(fl > mid) push(p<<1|1,fl,fr,id);
    }

    #undef ls
    #undef rs

}using namespace EWSegment;

vector<int> qu[MQ];

signed main(){
    read(n,m,q);
    n=BASEN;
    build(1,1,n,0);
    for(int i=1;i<=m;i++){
        int l1,l2,r1,r2,v;
        read(l1,l2,r1,r2,v);
        ql[l1].push_back({l2,r2,v});
        qr[r1].push_back({l2,r2,v});
    }
    for(int i=1;i<=q;i++){
        read(qry[i].l1,qry[i].l2,qry[i].r1,qry[i].r2);
        qry[i].id=i;
        push(1,qry[i].l1,qry[i].r1,i);
    }

    for(int i=1;i<=16;i++){
        fsg.build(1,1,n);
        vector<int> vis1;
        for(auto p:T[i-1]){
            for(auto id: t[p].ln){
                if(qry[id].r1 > t[p<<1].r) {
                    if(qu[qry[id].r1].empty()) vis1.push_back(qry[id].r1);
                    qu[qry[id].r1].push_back(id);
                }
            }
        }
        long long sum = 0;
        for(auto p:T[i]){
            if(p == ((t[p].fa<<1)|1)) {
                sum += BIG;
                fsg.add(1,1,n,BIG);
            }
            for(int j = t[p].l; j <= t[p].r; ++j){
                for(auto &ln: ql[j]){
                    fsg.add(1, ln.l, ln.r, ln.k);
                }
                for(auto id: qu[j]){
                    ans[id] = max(ans[id],fsg.queryhis(1, qry[id].l2, qry[id].r2) - sum);
                }
                for(auto &ln: qr[j]){
                    fsg.add(1, ln.l, ln.r, -ln.k);
                }
            }
        }
        for(auto pos: vis1) qu[pos].clear();

        reverse(T[i].begin(), T[i].end());
        fsg.build(1,1,n);

        vector<int> vis2;
        for(auto p:T[i-1]){
            for(auto id: t[p].ln){
                if(qry[id].l1 <= t[p<<1].r){
                    if(qu[qry[id].l1].empty()) vis2.push_back(qry[id].l1);
                    qu[qry[id].l1].push_back(id);
                }
            }
        }
        sum = 0;
        for(auto p:T[i]){
            if(p == (t[p].fa<<1)) {
                sum += BIG;
                fsg.add(1,1,n,BIG);
            }
            for(int j = t[p].r; j >= t[p].l; --j){
                for(auto &ln: qr[j]){
                    fsg.add(1, ln.l, ln.r, ln.k);
                }
                for(auto id: qu[j]){
                    ans[id] = max(ans[id],fsg.queryhis(1, qry[id].l2, qry[id].r2) - sum);
                }
                for(auto &ln: ql[j]){
                    fsg.add(1, ln.l, ln.r, -ln.k);
                }
            }
        }
        for(auto pos: vis2) qu[pos].clear();
    }

    for(int i=1;i<=q;i++){
        put(ans[i]);
    }
    return 0;
}
