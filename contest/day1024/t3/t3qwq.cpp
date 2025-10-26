#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=1e9+7;
struct Edge{
    int u,v,w;
}e[MN];
int n,m,K,ans,dtot,tag[MN];
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

namespace EXKru{
    int pre[MN],val[MN];

    void initpre(int n){
        for(int i=0;i<=n;i++){
            pre[i]=i;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    bool cmp(Edge x,Edge y){
        return x.w<y.w;
    }

    int build(){
        sort(e+1,e+m+1,cmp);
        dtot=n;
        for(int i=1;i<=m;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru!=rv){
                dtot++;
                val[dtot]=e[i].w;
                pre[ru]=pre[rv]=dtot;
                adj[dtot].push_back(ru);
                adj[dtot].push_back(rv);
                if(dtot==2*n-1) break;
            }
        }
        int cnt=0;
        for(int i=1;i<=dtot;i++){
            cnt+=root(i)==i;
        }
        return cnt;
    }
}using namespace EXKru;

namespace Tree{
    int siz[MN],dep[MN],htop[MN],hson[MN],fa[MN];

    void dfs1(int u,int pre){
        siz[u]=(u<=n);
        dep[u]=dep[pre]+1;
        fa[u]=pre;
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
            if(v==hson[u]||v==fa[u]) continue;
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
}using namespace Tree;

void init(){
    int LIM = 2 * n; 
    EXKru::initpre(LIM);
    for(int i=1;i<=LIM;i++){
        adj[i].clear();
        EXKru::val[i]=0;
        tag[i]=0;
        fa[i]=hson[i]=htop[i]=0;
        dep[i]=siz[i]=0;
    }
    ans=0;
    dtot=0;
}

void solve1(){
    dfs1(dtot,0);
    dfs2(dtot,dtot);
    for(int i=1;i<=m;i++){
        tag[lca(e[i].u,e[i].v)]++;   
    }
    long long local_ans = 0;
    for(int i=n+1;i<=dtot;i++){
        long long prod=1;
        for(auto v:adj[i]){
            prod = (prod * siz[v]) % MOD;
        }
        long long contrib = ((EXKru::val[i]-1)%MOD+MOD)%MOD;
        long long diff = (prod - tag[i]) % MOD;
        if(diff < 0) diff += MOD;
        local_ans = (local_ans + contrib * diff) % MOD;
    }
    ans = (local_ans % MOD + MOD) % MOD;
}

void solve2(){
    int root_dtot = EXKru::root(dtot);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(EXKru::root(i)==root_dtot) cnt++;
    }
    ans = (1LL * cnt * ((n - cnt + MOD) % MOD)) % MOD;
    ans = (ans * (K % MOD)) % MOD;
    ans = (ans % MOD + MOD) % MOD;
}

void solve(){
    read(n,m,K);
    init();
    for(int i=1;i<=m;i++){
        read(e[i].u,e[i].v,e[i].w);
    }
    int qwq=build();
    if(qwq>=3) ans=0;
    else if(qwq==2){
        solve2();
    }else{
        solve1();
    }
    put((ans%MOD+MOD)%MOD);
}

signed main(){
    int T;
    read(T);
    while(T--){
        solve();
    }
    return 0;
}
