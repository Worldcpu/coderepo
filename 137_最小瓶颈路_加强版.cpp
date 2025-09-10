#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7,ML=30;
struct Edge{
    int u,v,w;
}e[MN];
int pre[MN],n,m,ans,q,val[MN];
int A,B,C,P;
vector<int> adj[MN];
int hson[MN],dep[MN],top[MN],fa[MN],siz[MN];

void dfs1(int u,int pre){
    siz[u]=1;
    fa[u]=pre;
    dep[u]=dep[pre]+1;
    int maxp=-1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(maxp<siz[v]){
            hson[u]=v;
            maxp=siz[v];
        }
    }
}

void dfs2(int u,int ltop){
    top[u]=ltop;
    if(!hson[u]) return;
    dfs2(hson[u],ltop);
    for(auto v:adj[u]){
        if(v==fa[u]||v==hson[u]){
            continue;
        }
        dfs2(v,v);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}


int rnd(){
    return A=(A*B+C)%P;
}

void initpre(){
    for(int i=0;i<MN;i++) pre[i]=i;
}

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

bool cmp(Edge x,Edge y){
    return x.w<y.w;
}

void exkruskal(){
    int cnt=n;
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru!=rv){
            cnt++;
            pre[ru]=pre[rv]=cnt;
            val[cnt]=e[i].w;
            adj[cnt].push_back(ru);
            adj[cnt].push_back(rv);
            if(cnt==2*n-1) break;
        }
    }
}

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
    initpre();
    read(n,m);
    for(int i=1;i<=m;i++){
        read(e[i].u,e[i].v,e[i].w);
    }
    sort(e+1,e+1+m,cmp);
    exkruskal();
    dfs1(2*n-1,0);
    dfs2(2*n-1,2*n-1);
    read(q,A,B,C,P);
    while(q--){
        int u=rnd()%n+1,v=rnd()%n+1;
        if(u==v) continue;
        else ans=(ans+val[lca(u,v)])%MOD;
    }
    cout<<ans;
    return 0;
}