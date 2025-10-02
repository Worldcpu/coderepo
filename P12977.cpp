#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e7+15;
int p[MN],n,cur[MN];
ll sum[MN];
__int128 ans;
char ch[MN];

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

int len(int l,int r){
    return (r+1>>1)-(l>>1);
}

signed main(){
    read(n);
    ch[0]='$';
    for(int i=1;i<=n;i++){
        read(ch[2*i-1]);
        ch[2*i]='#';
    }
    n*=2;
    int r=0,c;
    for(int i=1;i<=n;i++){
        if(i<r){
            int lst=c*2-i;
            p[i]=p[lst];
            sum[i]=sum[lst],cur[i]=cur[lst];
            while(p[i]>r-i){
                if(cur[i]*2>=len(lst-p[i],lst+p[i])&&ch[lst+p[i]]!='#') sum[i]-=cur[i];
                cur[i]-=(ch[lst+p[i]]=='?')*2,p[i]--;
            }
        }else if(ch[i]=='?') cur[i]=sum[i]=1;
        while(ch[i+p[i]+1]==ch[i-p[i]-1]){
            p[i]++;
            cur[i]+=(ch[i+p[i]]=='?')*2;
            if(cur[i]*2>=len(i-p[i],i+p[i])&&ch[i+p[i]]!='#') sum[i]+=cur[i];
        }
        ans+=(__int128)sum[i]*(i+1)/2;
        if(p[i]+i>r){
            r=p[i]+i;
            c=i;
        }
    }
    put(ans);
    return 0;
}