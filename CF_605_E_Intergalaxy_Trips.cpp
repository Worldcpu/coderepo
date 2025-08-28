#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e3+15;
int n;
double p[MN][MN],f[MN],g[MN];
bool vis[MN];

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

int main(){
    read(n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            read(x);
            p[i][j]=x/100.0;
        }
        if(i==n) break;
        f[i]=1;
        g[i]=1-p[i][n];
    }
    vis[n]=1;
    if(n==1){
        put(0);
        return 0;
    }
    while(1){
        int u=0;
        double minn=1e18;
        for(int i=1;i<=n;i++){
            if(!vis[i]&&f[i]/(1-g[i])<minn){
                minn=f[i]/(1-g[i]);
                u=i;
            }
        }
        vis[u]=1;
        if(u==1) cout<<fixed<<setprecision(10)<<minn,exit(0);
        for(int i=1;i<=n;i++){
            if(vis[i]) continue;
            f[i]+=minn*p[i][u]*g[i];
            g[i]*=(1-p[i][u]);
        }
    }
    cout<<-1;
    return 0;
}