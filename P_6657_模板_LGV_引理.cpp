#include<bits/stdc++.h>
using namespace std;
constexpr int MN=150,MP=2e6,MOD=998244353;
int n,m,pw[MP],inv[MP],mt[MN][MN],a[MN],b[MN];

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


int ksm(long long a,int b){
    long long ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

namespace HLS{

    int solve(){
        int ret = 1, w = 1;
        for(int i = 1; i <= m; ++i){
            int k = i;
            while(k <= m && !mt[k][i]) ++k;
            if(k > m) return 0;
            if(k != i){
                for(int j = i; j <= m; ++j) swap(mt[i][j], mt[k][j]);
                w = -w;
            }
            ret = 1ll * ret * mt[i][i] % MOD;
            int invPivot = ksm(mt[i][i], MOD - 2);
            for(int j = i + 1; j <= m; ++j){
                int factor = 1ll * mt[j][i] * invPivot % MOD;
                for(int k = i; k <= m; ++k)
                    mt[j][k] = (mt[j][k] - 1ll * mt[i][k] * factor % MOD + MOD) % MOD;
            }
        }
        return (w * ret % MOD + MOD) % MOD;
    }

}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MP;i++){
        pw[i]=1ll*pw[i-1]*i%MOD;
    }
    inv[MP-1]=ksm(pw[MP-1],MOD-2);
    for(int i=MP-2;i>=0;i--){
        inv[i]=1ll*inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b) return 0;
    return 1ll*pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void solve(){
    read(n,m);
    for(int i=1;i<=m;i++){
        read(a[i],b[i]);
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            if(a[i]<=b[j]){
                mt[i][j]=getC(n-a[i]+b[j]-1,n-1);
            }else{
                mt[i][j]=0;
            }
        }
    }
    put(HLS::solve());
}

signed main(){
    initpw();
    int T;
    read(T);
    while(T--){
        solve();
    }
    return 0;
}
