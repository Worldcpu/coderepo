#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN = 3e5 + 15;
int n, K, a[MN], nxt[MN], ans[MN];

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

const int block_size = 550;
int b[MN];
struct block {
    int l, r, tag, ans, T;
    short c[MN]; 
    inline void breakdown() {
        for (int i = l; i <= r; ++i) {
            --c[a[i]];
            a[i] += tag;
        }
        tag = 0;
    }
    inline void build() {
        ans = 0;
        T = K;
        for (int i = l; i <= r; ++i) {
            ++c[a[i]];
            if (a[i] <= K)
                ++ans;
        }
    }
    inline void add(int w) {
        tag += w;
        if (w == 1) {
            if (T >= 0)
                ans -= c[T];
            --T;
        } else {
            for (int j = 1; j <= -w; ++j) {
                ++T;
                if (T >= 0)
                    ans += c[T];
            }
        }
    }
} blk[MN / block_size + 5];

static inline void whole_add(int x, int w) {
    for (int i = x; i <= b[n]; ++i)
        blk[i].add(w);
}
static inline void fast_add(int x, int w) {
    for (int i = x; i <= blk[b[x]].r; ++i)
        a[i] += w;
    whole_add(b[x] + 1, w);
}
static inline void add(int x, int w) {
    blk[b[x]].breakdown();
    for (int i = x; i <= blk[b[x]].r; ++i)
        a[i] += w;
    blk[b[x]].build();
    whole_add(b[x] + 1, w);
}
static inline int query(int x) {
    int ret = 0;
    for (int i = x; i <= blk[b[x]].r; ++i)
        if (a[i] + blk[b[x]].tag <= K)
            ++ret;
    for (int i = b[x] + 1; i <= b[n]; ++i)
        ret += blk[i].ans;
    return ret;
}

signed main() {
    read(n, K);
    for (int i = 1; i < n; ++i)
        read(nxt[i]);

    for (int i = 1; i <= n; ++i)
        blk[b[i] = (i - 1) / block_size + 1].r = i;
    for (int i = 1; i <= b[n]; ++i)
        blk[i].l = blk[i - 1].r + 1;

    for (int i = 1; i <= b[n]; ++i) {
        blk[i].tag = 0;
        blk[i].ans = 0;
        blk[i].T = K;
        memset(blk[i].c, 0, sizeof(blk[i].c));
    }

    ans[n] = 1;

    for (int i = b[n]; i; --i) {
        int l = blk[i].l, r = blk[i].r;
        for (int j = min(r, n - 1); j >= l; --j) {
            if (j == r)
                whole_add(i + 1, 1);
            else
                fast_add(j + 1, 1);

            if (nxt[j] <= r)
                fast_add(nxt[j], 1 - a[nxt[j]] - blk[b[nxt[j]]].tag);
            else
                add(nxt[j], 1 - a[nxt[j]] - blk[b[nxt[j]]].tag);

            int ret = 0;
            for (int o = j; o <= blk[i].r; ++o)
                if (a[o] <= K)
                    ++ret;
            for (int o = i + 1; o <= b[n]; ++o)
                ret += blk[o].ans;
            ans[j] = ret;
        }
        blk[i].build();
    }

    for (int i = 1; i <= n; ++i)
        put(ans[i], 0);
    put('\n', 0);
    return 0;
}
