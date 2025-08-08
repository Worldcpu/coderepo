#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
int n,buf[MN],*f[MN],*now;
int ans[MN];
vector<int> adj[MN];

namespace Tree{
    int dep[MN],son[MN];

    void dfs1(int u,int pre){
        dep[u]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            if(dep[v]+1 > dep[u]){
                dep[u] = dep[v]+1;
                son[u] = v;
            }
        }
    }

    void solve(int u,int pre){
        f[u][0] = 1;
        if(son[u]){
            f[son[u]] = f[u]+1;
            solve(son[u],u);
            ans[u] = ans[son[u]] + 1;
        }
        for(auto v:adj[u]){
            if(v==pre || v==son[u]) continue;
            f[v] = now;
            now += dep[v];
            solve(v,u);
            for(int i=1;i<=dep[v];i++){
                f[u][i] += f[v][i-1];
                if(f[u][i]>f[u][ans[u]] || (f[u][i]==f[u][ans[u]] && i<ans[u]))
                    ans[u]=i;
            }
        }
        if(f[u][ans[u]] == 1) ans[u] = 0;
    }

} using namespace Tree;

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
    } using namespace IO::usr;
} using namespace ly::IO::usr;

int main(){
    read(n);
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);                 // 正确计算子树高度 & 重儿子
    now=buf;
    f[1]=now;
    now+=dep[1];              // 分配根节点 DP 空间
    solve(1,0);
    for(int i=1;i<=n;i++){
        put(ans[i]);
    }
    return 0;
}
