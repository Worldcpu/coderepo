#include<bits/stdc++.h>
using namespace std;
constexpr int MN=4e5+15,MB=1e5;
struct Query{
    int l,r,K,id;
};
int n,m,bl,a[MN],b[MN],ans[MN],cnt[MN];
bitset<MN> f;
vector<Query> qry[MN];

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

bool mdcmp(Query x,Query y){
    if(x.l/bl==y.l/bl){
        if((x.l/bl)&1) return x.r<y.r;
        return x.r>y.r;
    }
    return x.l/bl<y.l/bl;
}

signed main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    for(int i=1;i<=m;i++){
        int l,r,k;
        read(l,r,k);
        qry[k].push_back({l,r,k,i});
    }
    for(int i=2;i<MN;i++){
        if(qry[i].empty()) continue;
        if(min(MB/i,MB>>6)*qry[i].size()<(n<<2)){
            qry[0].insert(qry[0].end(),qry[i].begin(),qry[i].end());
            continue;
        }
        bl=n/sqrt(qry[i].size()+1)+1;
        for(int j=1;j<=n;j++){
            b[j]=a[j]%i;
        }
        sort(qry[i].begin(),qry[i].end(),mdcmp);
        int l=1,r=0;
        for(auto p:qry[i]){
			while(l>p.l) (!cnt[b[--l]]++)&&(f[b[l]]=1);
			while(r<p.r) (!cnt[b[++r]]++)&&(f[b[r]]=1);
			while(l<p.l) (!--cnt[b[l]])&&(f[b[l]]=0),++l;
			while(r>p.r) (!--cnt[b[r]])&&(f[b[r]]=0),--r;
            for(int k=0;k<i;k++){
                if(f[k]){
                    ans[p.id]=k;
                    break;
                }
            }
        }
        f.reset();
        memset(cnt,0,sizeof(cnt));
    }
    if(!qry[0].empty()){
        bl=n/sqrt(qry[0].size()+1)+1;
        sort(qry[0].begin(),qry[0].end(),mdcmp);
        int l=1,r=0;
        for(auto p:qry[0]){
			while(l>p.l) (!cnt[a[--l]]++)&&(f[a[l]]=1);
			while(r<p.r) (!cnt[a[++r]]++)&&(f[a[r]]=1);
			while(l<p.l) (!--cnt[a[l]])&&(f[a[l]]=0),++l;
			while(r>p.r) (!--cnt[a[r]])&&(f[a[r]]=0),--r;
            ans[p.id]=1e9;
			for(int k=f._Find_first(); ans[p.id]&&k!=f.size(); k=(k/p.K+1)*p.K-1>=f.size()?f.size():f._Find_next((k/p.K+1)*p.K-1)) 
				(ans[p.id]>k%p.K)&&(ans[p.id]=k%p.K);
        }
    }
    for(int i=1;i<=m;i++) put(ans[i]);
    return 0;
}
