#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,X,cnt[MN],ans,tot;
vector<int> adj[MN];

struct Node{
    int a,b;

    Node(int aa=0,int bb=0){
        a=aa,b=bb;
    }

    friend bool operator<(const Node &x,const Node &y){
        return x.a*y.b<y.a*x.b;
    }

    friend Node operator+(const Node &x,const Node &y){
        return Node(x.a+y.a,x.b+y.b);
    }
};
multiset<Node> st[MN];

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

void dfs(int u,int pre){
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        if(st[u].size()<st[v].size()) swap(st[u],st[v]);
        st[u].merge(st[v]);
        st[v].clear();
    }
    if(cnt[u]==-1){
        st[u].insert(Node(0,1));
    }else if(st[u].empty()){
        tot+=cnt[u];
    }else{
        auto now=Node(cnt[u],0);
        do{
            auto tp=(*st[u].begin());
            st[u].erase(st[u].begin());
            ans+=now.b*tp.a;
            now=now+tp;
        }while(st[u].size()&&(*st[u].begin())<now);
        st[u].insert(now);
    }
}

signed main(){
    read(n,X);
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=2;i<=n;i++){
        int t,a,d,h;
        read(t);
        if(t==1){
            cnt[i]=-1;
        }else{
            read(a,d,h);
            cnt[i]=(h-1)/(X-d);
            ans-=(h-1)/(X-d)*a;           
        }
    }
    dfs(1,0);   
    int cur=0;
    for(auto p:st[1]){
        ans+=cur*p.a;
        cur+=p.b;
    }
    ans+=tot*cur;
    put(ans);
    return 0;
}