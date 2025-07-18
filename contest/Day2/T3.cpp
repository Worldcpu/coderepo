#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,INF=0x3f3f3f3f;
struct Edge{
    int v,w;
};
int n,m,q,ctot,fa[MN][30],dep[MN];
bool vis[MN];
vector<Edge> adj[MN];

struct DPNode{
    int v[2][2],c[2][2];

    void doswap(){
        swap(c[0],c[1]);
        swap(v[0][1],v[1][0]);
    }

    int getans(){
        return max({v[0][0],v[0][1],v[1][0],v[1][1]});
    }

    friend DPNode operator + (DPNode a,DPNode b){
        DPNode ret={-INF,-INF,-INF,-INF,a.c[0][0],a.c[0][1],b.c[1][0],b.c[1][1]};
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    for(int l=0;l<2;l++){
                        ret.v[i][l]=max(ret.v[i][l],a.v[i][j]+b.v[k][l]+(a.c[1][j]!=b.c[0][k]));
                    }
                }
            }
        }
        return ret;
    }

}f[MN][30];

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
    dep[u]=dep[pre]+1;
    fa[u][0]=pre;
    for(int i=1;i<=19;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    vis[u]=1;
    for(auto e:adj[u]){
        if(e.v==pre||vis[e.v]) continue;
        dfs(e.v,u);
    }
    if(!pre) return;
    int v0=0,v1=0;
    set<int> s;
    for(auto e:adj[u]){
        if(e.v!=pre) continue;
        if(!s.count(e.w)){
            if(!v0) v0=e.w;
            else v1=e.w;
            s.insert(e.w);
        }
    }
    if(s.size()>2){
        s.clear();
        s.insert(v0=++ctot);
    }
    if(s.size()==1){
        f[u][0]={0,-INF,-INF,-INF,v0,0,v0,0};
    }else f[u][0]={0,-INF,-INF,0,v0,v1,v0,v1};
}

int lca(int x,int y){
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    for(int i=19;i>=0;i--){
        if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    }
    if(x==y) return x;
    for(int i=19;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

DPNode clac(int x,int y){
    auto ret=f[x][0];
    x=fa[x][0];
    for(int i=19;i>=0;i--){
        if(dep[fa[x][i]]>=dep[y]){
            ret=ret+f[x][i];
            x=fa[x][i];
        }
    }
    return ret;
}

int query(int x,int y){
    if(x==y) return 0;
    int l=lca(x,y);
    auto retx=clac(x,l);
    auto rety=clac(y,l);
    rety.doswap();
    if(x==l) return rety.getans();
    else if(y==l) return retx.getans();
    else return (retx+rety).getans();
}

signed main(){
    freopen("trip.in","r",stdin);
    freopen("trip.out","w",stdout);
    read(n,m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        read(u,v,w);
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs(1,0);
    for(int j=1;j<=19;j++){
        for(int i=1;i<=n;i++){
            if(fa[i][j]){
                f[i][j]=f[i][j-1]+f[fa[i][j-1]][j-1];
            }
        }
    }
    read(q);
    while(q--){
        int x,y;
        read(x,y);
        int qwq=query(x,y);
        put(qwq);
    }
    return 0;
}
