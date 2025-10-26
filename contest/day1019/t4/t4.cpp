#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MP=4e6+15,MN=11520,MK=114,MOD=1e9+7;
int pw[MP],inv[MP],a[MN],num[MN],n,m,c;
int f[MN][MK],sum[MN][MK];

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

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MP;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MP-1]=ksm(pw[MP-1],MOD-2);
    for(int i=MP-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void init(){
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++){
        num[i]=0;
    }
    for(int i=1;i<=m;i++){
        a[i]=0;
        memset(sum[i],0,sizeof(sum[i]));
    }
}

void solve(){
    read(n,c,m);
    init();
    for(int i=1;i<=m;i++){
        read(a[i]);
        // num[a[i]]++;
        // if(num[a[i]]>c){
        //     cout<<0<<'\n';
        //     return;
        // }
    }
    for(int i=1;i<=n;i++){
        num[i]=count(a+1,a+1+m,i);
        if(num[i]>c){
            put(0);
            return;
        }
    }
    for(int i=1;i<=m;i++){
        memcpy(sum[i],sum[i-1],sizeof(sum[i]));
        for(int j=1;j<=a[i];j++){
            sum[i][j]++;
        }
    }
    f[1][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=(!a[i]?n:a[i]);j++){
            for(int k=c;k>=1;k--){
                f[j][k]=f[j][k-1];
            }
            f[j][0]=0;
        }
        for(int j=(!a[i]?n:a[i])+1;j<=n+1;j++){
            memset(f[j],0,sizeof(int)*(c+1));
        }
        for(int j=1;j<=n;j++){
            for(int k=num[j];k<=c-sum[i][j+1];k++){
                f[j+1][c-k]=(f[j+1][c-k]+f[j][c]*getC(c-sum[i][j],k-num[j])%MOD)%MOD;
            }
            f[j][c]=0;
        }
    }
    put(f[n+1][0]);
}

signed main(){
    initpw();
    int T;
    read(T);
    while(T--){
        solve();
    }
}