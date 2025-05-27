#include<bits/stdc++.h>
#include <cmath>
#define int long long
using namespace std;
map<int,int> mp;

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

int qpow(int a,int b,int MOD){
    int ret=1;
    while(b){
        if(b&1){
            ret=ret*a%MOD;
        }
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

int BSGS(int a,int b,int p){
    mp.clear();
    b%=p;
    int t=sqrt(p)+1;
    for(int j=0;j<t;j++){
        int val=b*qpow(a,j,p)%p;
        mp[val]=j;
    }
    a=qpow(a,t,p);
    if(a==0) return b==0?1:-1;
    for(int i=0;i<=t;i++){
        int val=qpow(a,i,p);
        int j=mp.find(val)==mp.end()?-1:mp[val];
        if(j>=0&&i*t-j>=0) return i*t-j;
    }
    return -1;
}


int exBSGS(int a,int b,int p){
    a%=p,b%=p;// 战术取余，因为以及是转线性同余可以这样做
    if(b==1||p==1) return 0;
    int gcdd,d=1,cnt=0,x,y;
    while((gcdd=exgcd(a,p,x,y))^1){
        if(b%gcdd) return -1;// 如果无解
        b/=gcdd,p/=gcdd;
        cnt++;
        d=1ll*d*(a/gcdd)%p; // 累计d
        if(d==b) return cnt;
    }

    exgcd(d,p,x,y);
    int inv=(x%p+p)%p;
    b=1ll*b*inv%p;
    int ans=BSGS(a,b,p);
    if(ans==-1) return -1;
    else return ans+cnt;
}


signed main(){
    int a,p,b;
    while(1){
        read(a,p,b);
        if(a==0&&b==0&&p==0) break;
        int ans=exBSGS(a,b,p);
        if(ans==-1) put("No Solution");
        else put(ans);
    }
    return 0;
}
