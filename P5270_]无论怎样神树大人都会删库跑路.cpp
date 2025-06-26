#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=3e6+15,MOD=1e9+7;
int n,q,T,m,Thsh,bel[MN],ans[MN],pre[MN],a[MN],len[MN],R[MN];
mt19937 mt;
vector<int> s[MN],suf[MN];
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

int rand(int l,int r){
    return mt()%(r-l+1)+l;
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int gethsh(int x){
    return ksm(mp[x],x);
}

void inithsh(){
    for(int i=0;i<MN;i++){
        mp[i]=rand(1,1e9);
    }
}

signed main(){
    mt.seed(time(0));
    read(n,T,q);
    inithsh();
    for(int i=1;i<=T;i++){
        read(a[i]);
        (Thsh+=gethsh(a[i]))%=MOD;
    }
    for(int i=1;i<=n;i++){
        read(len[i]);
        s[i].resize(len[i]+1);
        suf[i].resize(len[i]+1);
        for(int j=1;j<=len[i];j++){
            read(s[i][j]);
        }
        suf[i][len[i]]=gethsh(s[i][len[i]]);
        for(int j=len[i]-1;j>=1;j--){
            suf[i][j]=(suf[i][j+1]+gethsh(s[i][j]))%MOD;
        }
    }
    read(m);
    for(int i=1;i<=m;i++){
        read(R[i]);
    }
    int now=0,l=1;
    for(int i=1;i<=min(q,1000000ll);i++){
        int p=R[(i-1)%m+1];
        bel[i]=p;
        pre[i]=pre[i-1]+len[p];
        now+=suf[p][1];
        if(pre[i]<T) continue;
        while(pre[i]-pre[l]>=T) (now=(now-suf[bel[l]][1]+MOD)%MOD),l++;
        if(Thsh == (now - suf[bel[l]][1] + suf[bel[l]][ len[bel[l]] - (T - (pre[i]-pre[l])) + 1 ] + MOD) % MOD){
            ans[i]=1;
        }
    }
    int ret=0;
    for(int i=1;i<=min(q,1000000ll);i++){
        if(i+m>1e6&&ans[i]){
            ans[i]=(q-i)/m+1;
        }
        ret+=ans[i];
    }
    cout<<ret;
    return 0;
}
