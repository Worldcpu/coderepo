#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int f[2][MN],nxt[MN],n,m;
string s,t;

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


void getnxt(){
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        while(j>0&&t[i]!=t[j+1]) j=nxt[j];
        if(t[i]==t[j+1]) j++;
        nxt[i]=j;
    }
}

int main(){
    read(s,t);
    n=s.length(),m=t.length();
    s=" "+s,t=" "+t;
    getnxt();
    memset(f,128,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=n;i++){
        int now=i&1,lst=!now;
        for(int j=0;j<=m;j++) f[now][j]=-1e9;
        for(int j=1;j<=m;j++){
            if(s[i]==t[j]||s[i]=='?'){
                f[now][j]=f[lst][j-1];
            }
            if(j==m){
                f[now][j]++;
                for(int k=nxt[m];k;k=nxt[k]){
                    f[now][k]=max(f[now][k],f[now][j]);
                }
            }
        }
        for(int j=0;j<=m;j++){
            f[now][0]=max({f[now][0],f[now][j],f[lst][j]});
        }
    }
    put(f[n&1][0]);
    return 0;
}
