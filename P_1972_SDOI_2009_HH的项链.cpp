#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
struct Query{
    int x,op,id;
};
int n,m,a[MN],pre[MN],lst[MN],ans[MN];
vector<Query> q[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int k){
        x++;
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        x++;
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

}bit;

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


int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    for(int i=1;i<=n;i++){
        pre[i]=lst[a[i]];
        lst[a[i]]=i;
        cerr<<pre[i]<<" ";
    }
    read(m);
    for(int i=1;i<=m;i++){
        int l,r;
        read(l),read(r);
        q[l-1].push_back({l-1,-1,i});
        q[r].push_back({l-1,1,i});
    }
    for(int i=1;i<=n;i++){
        bit.update(pre[i],1);
        for(auto v:q[i]){
            ans[v.id]+=v.op*bit.query(v.x);
        }
    }
    for(int i=1;i<=m;i++){
        put(ans[i]);
    }
    return 0;
}
