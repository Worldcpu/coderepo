#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr long long MN=55,MOD=1e6+3;
int n,K,T,len,tot,del[MN];
long long f[MN],pw[MN],pww[MN],inv[MN];
string s[MN];
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

void dfs(int x,int cnt){
    if(n-x+1+cnt<K) return;
    if(x==n+1){
        (f[cnt]+=pw[len-tot])%=MOD;
        return;
    }
    dfs(x+1,cnt);
    for(int i=0;i<len;i++){
        if(ch[i]&&s[x][i]>='a'&&ch[i]!=s[x][i]) return;
    }
    int lst=tot;
    for(int i=0;i<len;i++){
        if(!ch[i]&&s[x][i]!='?'){
            ch[i]=s[x][i];
            del[++tot]=i;
        }
    }
    dfs(x+1,cnt+1);
    while(tot>lst) ch[del[tot--]]=0;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pww[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void solve(){
    read(n,K);
    for(int i=1;i<=n;i++){
        read(s[i]);
    }
    len=s[1].length();
    for(int i=K;i<=n;i++) f[i]=0;
    dfs(1,0);
    ll ans=0;
    for(int i=K;i<=n;i++){
        if((i-K)&1) ans=(ans-getC(i,K)*f[i]%MOD+MOD)%MOD;
        else (ans+=getC(i,K)*f[i]%MOD)%=MOD;
    }
    put(ans);
}

long long ksm(long long a,int b){
    long long ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*26%MOD;
    pww[0]=1;
    for(int i=1;i<MN;i++) pww[i]=pww[i-1]*i%MOD;
    inv[MN-1]=ksm(pww[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

signed main(){
    init();
    read(T);
    while(T--){
        solve();
    }

    return 0;
}
