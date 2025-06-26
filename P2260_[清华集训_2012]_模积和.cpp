#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MOD=19940417,INV2=9970209,INV6=3323403;
int n,m,n1,ans1,ans2,ans3;

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

int getsum(int l,int r){
    return (r-l+1)*(l+r)%MOD*INV2%MOD;
}

int getpfsum(int x){
    return x*(x+1)%MOD*(2*x+1)%MOD*INV6%MOD;
}

signed main(){
    read(n,m);
    if(n>m) swap(n,m);
    ans1=n*n%MOD;
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        ans1=(ans1-(n/l)*getsum(l,r)+MOD)%MOD;
    }
    ans2=m*m%MOD;
    for(int l=1,r;l<=m;l=r+1){
        r=m/(m/l);
        ans2=(ans2-(m/l)*getsum(l,r)+MOD)%MOD;
    }
    for(int l=1,r;l<=n;l=r+1){
        r=min(n/(n/l),m/(m/l));
        int x,y,z;
        x=(r-l+1)*n%MOD*m%MOD;
        y=getsum(l,r)*((n/l)*m+(m/l)*n)%MOD;
        z=(getpfsum(r)-getpfsum(l-1)+MOD)%MOD*(n/l)%MOD*(m/l)%MOD;
        ans3=(ans3+x-y+z+MOD)%MOD;
    }
    put((ans1*ans2%MOD-ans3+MOD)%MOD);
    return 0;
}
