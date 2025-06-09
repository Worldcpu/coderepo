#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=3e5+15;
int n,m,gtag,a[MN],pre[MN],tag[MN];
multiset<int> mx;
multiset <pir,greater<pir>> s[MN];

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

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void merge(int x,int y){
    int rx=root(x),ry=root(y);
    if(rx==ry) return;
    if(s[rx].size()>s[ry].size()) swap(rx,ry);
    pre[rx]=ry;
    mx.erase(mx.find(min((s[ry].begin())->first+tag[ry],(s[rx].begin()->first)+tag[rx])));
    for(auto p:s[rx]){
        a[p.second]=p.first-tag[ry]+tag[rx];
        s[ry].insert(pir(a[p.second],p.second));
    }
    s[rx].clear();
}

int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
        s[i].insert(pir(a[i],i));
        mx.insert(a[i]);
        pre[i]=i;
    }
    read(m);
    while(m--){
        string op;
        int x,y;
        read(op);
        if(op[0]=='U'){
            read(x,y);
            merge(x,y);
        }
        if(op[0]=='A'&&op[1]=='1'){
            read(x,y);
            int rx=root(x);
            mx.erase(mx.find((*s[rx].begin()).first+tag[rx]));
            s[rx].erase(s[rx].find(pir(a[x],x)));
            a[x]+=y;
            s[rx].insert(pir(a[x],x));
            mx.insert((*s[rx].begin()).first+tag[rx]);
        }
        if(op[0]=='A'&&op[1]=='2'){
            read(x,y);
            int rx=root(x);
            int p=(*s[rx].begin()).first+tag[rx];
            mx.erase(mx.find(p));
            tag[rx]+=y;
            mx.insert(p+y);
        }
        if(op[0]=='A'&&op[1]=='3'){
            read(x);
            gtag+=x;
        }
        if(op[0]=='F'&&op[1]=='1'){
            read(x);
            put(a[x]+tag[root(x)]+gtag);
        }
        if(op[0]=='F'&&op[1]=='2'){
            read(x);
            int rx=root(x);
            put((*s[rx].begin()).first+tag[rx]+gtag);
        }
        if(op[0]=='F'&&op[1]=='3'){
            put(*--mx.end()+gtag);
        }
    }
    return 0;
}
