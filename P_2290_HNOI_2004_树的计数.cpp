#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MN=155;
constexpr int MOD=100000000000000000+3;

int pw[MN], inv[MN], d[MN], n;

namespace ly {
    namespace IO {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn], out[maxn], *p1=in, *p2=in, *p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr {
            template<typename type>
            inline type read(type &x){
                x=0; bool flag(0); char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-', ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
                return flag?x=-x:x;
            }
            inline void write(int x){
                if(x<0) x=-x, putchar('-');
                static short stk[50]; int top=0;
                do stk[++top]=x%10, x/=10; while(x);
                while(top) putchar(stk[top--]|48);
            }
            template<typename type>
            inline void put(const type &x, bool flag=1){write(x); if(flag) putchar('\n');}
        }
    } using namespace IO::usr;
} using namespace ly::IO::usr;

int ksm(int a, int b){
    int ret=1;
    while(b){
        if(b&1) ret = (__int128)ret * a % MOD;
        a = (__int128)a * a % MOD;
        b >>= 1;
    }
    return ret;
}

signed main(){
    read(n);
    int sumd=0;
    for(int i=1;i<=n;i++){
        read(d[i]);
        sumd += d[i];
    }

    if(sumd != (__int128)(n-1)*2){
        put(0);
        return 0;
    }
    if(n==1){
        put(1);
        return 0;
    }

    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i] = (__int128)pw[i-1] * i % MOD;
    inv[n] = ksm(pw[n], MOD-2);
    for(int i=n-1;i>=0;i--) inv[i] = (__int128)inv[i+1] * (i+1) % MOD;

    int ans = pw[n-2];
    for(int i=1;i<=n;i++) ans = (__int128)ans * inv[d[i]-1] % MOD;

    put(ans);
    return 0;
}
