#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MN=55;
int n,ans,xn,a[MN],f[2][2][2],now;


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

signed main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        xn^=a[i];
    }
    ans=!xn,xn=0;
    for(int i=31;i>=0;i--){
        memset(f,0,sizeof(f));
        f[0][0][0]=1;
        for(int j=1,to=1,lst=0;j<=n;j++,swap(to,lst)){
            int tmp=(a[j]&((1<<i)-1))+1;
            xn^=a[j]>>i+1;
            for(int c=0;c<2;c++){
                for(int d=0;d<2;d++){
                    f[to][c^a[j]>>i&1][d]=f[lst][c][d]*tmp;
                }
            }
            if(a[j]>>i&1){
                for(int c=0;c<2;c++){
                    f[to][c][1]+=(f[lst][c][1]<<i)+f[lst][c][0];
                }
            }
        }
        if(!xn) ans+=f[n&1][0][1];
        else break;
    }
    put(ans-1);
    return 0;
}
