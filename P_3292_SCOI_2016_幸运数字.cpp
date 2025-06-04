#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e4+15,MP=66;
int n,q,g[MN];
int fa[MN],dep[MN],siz[MN],htop[MN],hson[MN];
vector<int> adj[MN];

struct xxj{
    int p[MP],pos[MP];
    
    void clear(){
        memset(p,0,sizeof(p));
        memset(pos,0,sizeof(pos));
    }

    void insert(int x,int y){
        for(int i=63;i>=0;i--){
            if((x>>i)&1){
                if(!p[i]){
                    p[i]=x;
                    pos[i]=y;
                    break;
                }
                else{
                    if(dep[pos[i]]<dep[y]){
                        swap(pos[i],y);
                        swap(x,p[i]);
                    }
                    x^=p[i];
                }
            }
        }
    }

    int getmx(){
        int ans=0;
        for(int i=63;i>=0;i--){
            if((ans^p[i])>ans) ans^=p[i];
        }
        return ans;
    }

}xj[MN];

struct Tree{

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        fa[u]=pre;
        siz[u]=1;
        xj[u]=xj[pre];
        xj[u].insert(g[u],u);
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

}t;

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

signed main(){
    read(n,q);
    for(int i=1;i<=n;i++){
        read(g[i]);
    }
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    t.dfs1(1,0);
    t.dfs2(1,1);
    xxj tmp;
    while(q--){
        tmp.clear();
        int x,y;
        read(x,y);
        int qlca=t.lca(x,y),dlca=dep[qlca];
        for(int i=0;i<=63;i++){
            if(dep[xj[x].pos[i]]>=dlca) tmp.insert(g[xj[x].pos[i]],0);
            if(dep[xj[y].pos[i]]>=dlca) tmp.insert(g[xj[y].pos[i]],0);
        }
        put(tmp.getmx());
    }
    return 0;
}
