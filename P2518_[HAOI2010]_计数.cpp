#include<bits/stdc++.h>
#define int __int128
using namespace std;
constexpr int MN=55,MOD=9223372036854775837;
int len,a[MN],ans,cnt[10],inv[MN];
int pw[MN]={ 1 , 1 , 2 , 6 , 24 , 120 , 720 , 5040 , 40320 , 362880 , 3628800 , 39916800 , 479001600 , 6227020800 , 87178291200 , 1307674368000 , 20922789888000 , 355687428096000 , 6402373705728000 , 121645100408832000 , 2432902008176640000 , 4974081987435560815 , 7972711318179803723 , 8128291617894744726 , 1388186055523580847 , 7034535277525193664 , 7653848515414294361 , 3739725105380879333 , 3255210545262087117 , 2167385444052768023 , 457959063599609831 , 4973358934733128924 , 2350161284928936339 , 3768346107816692491 , 8219931186655458813 , 1773058390443007508 , 8489869834819615266 , 530534635263386384 , 1713572066299130918 , 2265706327682674943 , 7617904775614015187 , 7962818583967020046 , 2396987199842911800 , 1613357187842673193 , 6424112007094189633 , 3160507176740482538 , 7032749577240559193 , 7721208840389127776 , 1683142864487099768 , 8687024065029681936 , 852717519309632461 , 6595105337372152163 , 1680712179725206507 , 6067397193742962338 , 4821427172202811957 };
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

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
    put("inv[MN]={",0);
    for(int i=0;i<MN;i++) put(inv[i],0),put(",",0);
    put("}");
}

signed main(){
    init();
    read(s);
    len=s.length();
    s=" "+s;
    for(int i=1;i<=len;i++){
        a[i]=(s[i]-'0');
        cnt[a[i]]++;
    }
    for(int i=1;i<=len;i++){
        for(int j=0;j<a[i];j++){
            if(!cnt[j]) continue;
            cnt[j]--;
            int sum=0,prod=1;
            for(int k=0;k<=9;k++) sum+=cnt[k];
            prod=pw[sum];
            for(int k=0;k<=9;k++) prod=prod*inv[cnt[k]]%MOD;
            cnt[j]++;
            (ans+=prod)%=MOD;
        }
        cnt[a[i]]--;
    }
    put(ans);   
    return 0;
}
