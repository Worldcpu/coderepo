#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,MOD=1e9+7;
int pre[MN],len,ppm[MN][30];
string s;


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

void getpre(string s){
    pre[1]=0;
    for(int i=2;i<=len;i++){
        int j=pre[i-1];
        while(j>0&&s[i]!=s[j+1]) j=pre[j];
        if(s[i]==s[j+1]) j++;
        pre[i]=j;
        ppm[i][0]=pre[i];
    }
}

void solve(){
    read(s);
    len=s.length();
    s=" "+s;
    getpre(s);
    for(int i=1;i<=20;i++){
        for(int j=1;j<=len;j++){
            ppm[j][i]=ppm[ppm[j][i-1]][i-1];
        }
    }
    int ans=1;
    for(int i=2;i<=len;i++){
        int p=i;
        for(int j=20;j>=0;j--){
            if(ppm[p][j]*2>i){
                p=ppm[p][j];
            }
        }
        int ret=0;
        for(int j=20;j>=0;j--){
            if(ppm[p][j]){
                ret+=1<<j;
                p=ppm[p][j];
            }
        }
        ans=ans*(ret+1)%MOD;
    }
    put(ans);
}

signed main(){
    int T;
    read(T);
    while(T--){
        solve();
    }
    return 0;
}
