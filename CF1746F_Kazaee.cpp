#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,MOD=1e9+7;
int n,q,a[MN],b[MN],c[MN],rd[MN],tot,op[MN],L[MN],R[MN],K[MN];
bool ans[MN];
mt19937 mt;
unordered_map<int,int> mp;

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


struct BIT{
    int t[MN];

    int lowbit(int x){ return x&-x; }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int query(int fl,int fr){
        return query(fr)-query(fl-1);
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    void clear(){
        memset(t,0,sizeof(t));
    }

}t;



signed main(){
    mt.seed(time(0));
    int tim=clock();
    read(n,q);
    for(int i=1;i<=n;i++){
        read(a[i]);
        b[++tot]=a[i];
    }
    for(int i=1;i<=q;i++){
        read(op[i],L[i],R[i]);
        if(op[i]==1){
            b[++tot]=R[i];
        }
        else{
            read(K[i]);
            ans[i]=(R[i]-L[i]+1)%K[i]==0;
        }
    }
    sort(b+1,b+1+tot);
    tot=unique(b+1,b+1+tot)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
    }
    for(int i=1;i<=q;i++){
        if(op[i]==1) R[i]=lower_bound(b+1,b+1+tot,R[i])-b;
    }
    for(;1.0*clock()-tim<=2.8*CLOCKS_PER_SEC;){
        t.clear();
        for(int i=0;i<=tot;i++){
            mp[i]=mt()%MOD;
        }
        for(int i=1;i<=n;i++) c[i]=mp[a[i]];
        for(int i=1;i<=n;i++) t.modify(i,c[i]);
        for(int i=1;i<=q;i++){
            if(op[i]==1){
                t.modify(L[i],mp[R[i]]-c[L[i]]);
                c[L[i]]=mp[R[i]];
            }else if(t.query(L[i],R[i])%K[i]) ans[i]=0;
        }
    }
    for(int i=1;i<=q;i++){
        if(op[i]!=1){
            put((ans[i]?"YES":"NO"));
        }
    }
    return 0;
}
