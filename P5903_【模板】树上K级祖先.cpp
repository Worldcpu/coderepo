#include<bits/stdc++.h>
#define ui unsigned int
using namespace std;
constexpr int MN=1e6+15;
int n,q,rt,hb[MN];
ui s;
long long ans;
vector<int> adj[MN];

namespace Tree{
    int dep[MN],mxdep[MN],fa[21][MN],hson[MN],htop[MN];
    vector<int> up[MN],dw[MN];

    void dfs1(int u,int pree){
        dep[u]=mxdep[u]=dep[pree]+1;
        fa[0][u]=pree;
        for(int i=1;i<=20;i++){
            fa[i][u]=fa[i-1][fa[i-1][u]];
        }
        for(auto v:adj[u]){
            if(v==pree) continue;
            dfs1(v,u);
            if(mxdep[v]>mxdep[u]){
                mxdep[u]=mxdep[v];
                hson[u]=v;
            }
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(u==ltop){
            for(int i=0,it=u;i<=mxdep[u]-dep[u];i++){
                up[u].push_back(it),it=fa[0][it];
            }
            for(int i=0,it=u;i<=mxdep[u]-dep[u];i++){
                dw[u].push_back(it),it=hson[it];
            }
        }
        if(hson[u]) dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[0][u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int query(int x,int k){
        if(!k) return x;
        x=fa[__lg(k)][x];
        k-=1<<(__lg(k));
        k-=dep[x]-dep[htop[x]];
        x=htop[x];
        return k>=0?up[x][k]:dw[x][-k];
    }

}using namespace Tree;

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

ui get(ui x){
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return s = x; 
}

signed main(){
    read(n,q,s);
    for(int i=1;i<=n;i++){
        int faa;
        read(faa);
        if(!faa){
            rt=i;
            continue;
        }
        adj[faa].push_back(i);
        adj[i].push_back(faa);
    }
    dfs1(rt,0);
    dfs2(rt,rt);
    int lst=0;
    for(int i=1;i<=q;i++){
        int x,k;
        x=(get(s)^lst)%n+1;
        k=(get(s)^lst)%dep[x];
        lst=query(x,k);
        ans^=1ll*i*(lst);
    }
    cout<<ans;
    return 0;
}
