#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2520;
int a[MN][MN],sum[MN][MN],n,m,K,ans,up[2][MN];

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

int calc(int xl,int xr,int yl,int yr){
    return sum[xr][yr]-sum[xr][yl]-sum[xl][yr]+sum[xl][yl];
}

void cdq(int xl,int xr,int yl,int yr,int st){
    if(xl==xr||yl==yr) return;
    if(xl+1==xr&&yl+1==yr){
        ans+=(calc(xl,xr,yl,yr)==K);
        return;
    }
    int midx=(xl+xr)>>1,midy=(yl+yr)>>1;
    if(st==0){
        cdq(xl,midx,yl,yr,st^1);
        cdq(midx,xr,yl,yr,st^1);
        for(int i=yl;i<=yr;i++){
            up[0][0]=up[1][0]=midx;
            for(int j=1;j<=K+1;j++){
                up[0][j]=xl,up[1][j]=xr;
            }
            for(int j=i+1;j<=yr;j++){
                for(int k=1;k<=K+1;k++){
                    while(calc(up[0][k],midx,i,j)>=k) up[0][k]++;
                    while(calc(midx,up[1][k],i,j)>=k) up[1][k]--;
                }
                for(int k=0;k<=K;k++){
                    ans+=(up[0][k]-up[0][k+1])*(up[1][K-k+1]-up[1][K-k]);
                }
            }
        }
    }else{
        cdq(xl,xr,yl,midy,st^1);
        cdq(xl,xr,midy,yr,st^1);
        for(int i=xl;i<=xr;i++){
            up[0][0]=up[1][0]=midy;
            for(int j=1;j<=K+1;j++){
                up[0][j]=yl,up[1][j]=yr;
            }
            for(int j=i+1;j<=xr;j++){
                for(int k=1;k<=K+1;k++){
                    while(calc(i,j,up[0][k],midy)>=k) up[0][k]++;
                    while(calc(i,j,midy,up[1][k])>=k) up[1][k]--;
                }
                for(int k=0;k<=K;k++){
                    ans+=(up[0][k]-up[0][k+1])*(up[1][K-k+1]-up[1][K-k]);
                }
            }
        }
    }
    

}

signed main(){
    read(n,m,K);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char x;
            read(x);
            a[i][j]=(x-'0');
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]=a[i][j]-sum[i-1][j-1]+sum[i-1][j]+sum[i][j-1];
        }
    }
    cdq(0,n,0,m,1);
    put(ans);
    return 0;
}