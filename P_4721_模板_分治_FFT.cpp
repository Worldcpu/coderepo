#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e7+15;
int len,n,m;

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

namespace BJXPoly{
    const double pi=acos(-1);
    constexpr int MXREV=1e7;
    using compd=complex<double>;
    int rev[MN];
    compd tmp[MN],tf[MN],tg[MN],f[MN],g[MN];


    void dorev(compd f[],int len){
        for(int i=0;i<len;i++){
            rev[i]=rev[i>>1]>>1;
            if(i&1){
                rev[i]|=len>>1;
            }
        }
        for(int i=0;i<len;i++){
            if(i<rev[i]) swap(f[i],f[rev[i]]);
        }
    }

    void fft(compd f[],int len,int mode){
        dorev(f,len);
        for(int i=2;i<=len;i<<=1){//处理的区间长度
            compd wn(cos(2*pi/i),sin(2*pi*mode/i));
            for(int j=0;j<len;j+=i){//步长为i
                compd w(1,0);
                for(int k=j;k<j+i/2;k++){// 蝶形优化
                    compd u=f[k];//左区间
                    compd t=w*f[k+i/2];//右区间
                    f[k]=u+t;
                    f[k+i/2]=u-t;
                    w=w*wn;
                }
            }
        }
        if(mode==-1){
            for(int i=0;i<len;i++){
                f[i]/=len;
            }
        }
    }
    
    // F is the out ans
    void Mul(compd F[],compd G[],int n,int m){
        int len=1;
        while(len<=n+m) len<<=1;
        fft(F,len,1);
        fft(G,len,1);
        for(int i=0;i<len;i++) F[i]=F[i]*G[i];
        fft(F,len,-1);
    }

    // Ans is the out,The second state is the len
    pair<compd*,int> MulAns(compd F[],compd G[],compd Ans[],int n,int m){
        int len=1;
        while(len<=n+m) len<<=1;
        fft(F,len,1);
        fft(G,len,1);
        for(int i=0;i<len;i++) Ans[i]=F[i]*G[i];
        fft(Ans,len,-1);
        return pair<compd*,int>(Ans,len);
    }


    void cdq(int l,int r){
        if(l+1==r) return;
        int mid=(l+r)>>1;
        int len=r-l;
        cdq(l,mid);
        for(int i=0;i<len*2;i++){
            tmp[i]=0;
        }
        for(int i=l;i<mid;i++) tmp[i-l]=f[i];
        Mul(tmp,g,len*2,len*2);
        for(int i=mid;i<r;i++) (f[i]+=tmp[i-l])%=MOD;
        cdq(mid,r);
    }

}

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>BJXPoly::g[x];
    }
    int lim=n;
    while(lim!=(1<<__lg(lim))) ++lim;
    f[0]=1;
    BJXPoly::cdq(0,lim);
    for(int i=0;i<n;i++){
        put(f[i],0);
    }
    return 0;
}