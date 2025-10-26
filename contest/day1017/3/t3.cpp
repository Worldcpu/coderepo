#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=8e5+15,ML=30;
int n,q,btot;
bool vis[MN];
vector<int> adj[MN];

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

struct Segment{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int qwq,int x,int k){
        while(x<=n){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x>0){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int querysum(int qwq,int l,int r){
        return query(r)-query(l-1);
    }

}sg;

namespace Tree{
    int dfn[MN],id[MN],siz[MN],dtot,fa[ML+1][MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        dfn[u]=++dtot;
        fa[0][u]=pre;
        id[dtot]=u;
        for(int i=1;i<=ML;i++){
            fa[i][u]=fa[i-1][fa[i-1][u]];
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
        }
    }
}using namespace Tree;

bool check(int fax,int x){
    int ret=sg.querysum(1,dfn[fax],dfn[x])+sg.querysum(1,dfn[x]+siz[x]-1,dfn[fax]+siz[fax]-1);
    return ret>0;
}

signed main(){
    read(n,q);
    for(int i=2;i<=n;i++){
        int fa;
        read(fa);
        adj[fa].push_back(i);
        adj[i].push_back(fa);
    }
    dfs1(1,0);
    while(q--){
        int x;
        read(x);
        if(x>0){
            if(vis[x]){
                sg.modify(1,dfn[x],-1);
                vis[x]=0;           
                btot--;
            }else{
                sg.modify(1,dfn[x],1);
                vis[x]=1;           
                btot++;
            }
        }else{
            if(!btot){
                put(0);
                continue;
            }
            x=-x;
            if(vis[x]==1||sg.querysum(1,dfn[x],dfn[x]+siz[x]-1)>0){
                put(x);
                continue;
            }
            int p=x;
            for(int i=ML;i>=0;i--){
                if(fa[i][p]&&!check(fa[i][p],p)) p=fa[i][p];
            }
            put(fa[0][p]);
        }
    }
    return 0;
}

// nlog^2 n 很简单，nlogn 不简单。
// 反着做没法做，正着做没法做，但是可以用小技巧。