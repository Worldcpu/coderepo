#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,w;
};
struct EDGE{
    int u,v,w;
}e[MN];
int n,K,sumn,t[MN];
ll ans;
bool tagr[MN];
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

namespace DSU{
    int pre[MN];

    void initpre(){
        for(int i=0;i<=2*n;i++){
            pre[i]=i;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

}using namespace DSU;

namespace EXKru{
    int dtot,val[MN];
    
    bool cmp(EDGE x,EDGE y){
        return x.w<y.w;
    }

    void build(){
        sort(e+1,e+n,cmp);
        dtot=n;
        for(int i=1;i<n;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru==rv) continue;
            dtot++;
            val[dtot]=e[i].w;
            adj[dtot].push_back(ru);
            adj[dtot].push_back(rv);
            pre[ru]=pre[rv]=dtot;           
            if(dtot==2*n-1) break;
        }
    }   
}using namespace EXKru;

namespace Tree{
    ll val1[MN],val2[MN],siz0[MN],siz1[MN],htop[MN];

    void dfs1(int u,int pre){
        if(u>=1&&u<=n){
            siz0[u]+=t[u]==0;
            siz1[u]+=t[u]==1;
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz0[u]+=siz0[v];
            siz1[u]+=siz1[v];
            tagr[u]|=tagr[v];
        }
    }

    void dfs2(int u,int pre,int ltop){
        val1[u]=val1[pre]+siz0[u]*val[u]-siz0[u]*val[pre];
        val2[u]=val2[pre]+siz1[u]*val[u]-siz1[u]*val[pre];
        ltop=(tagr[u]?u:ltop);
        if(u>=1&&u<=n){
            htop[u]=ltop;
            return;
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs2(v,u,ltop);
        }
    }

}using namespace Tree;

ll calc0(int x){
    if(!t[x]) return val2[htop[x]];
    else return val2[htop[x]]-val[htop[x]];
}

ll calc1(int x){
    if(t[x]) return val1[htop[x]];
    else return val1[htop[x]]-val[htop[x]];
}

void init(){
    for(int i=1;i<=dtot;i++){
        adj[i].clear();
        tagr[i]=val1[i]=val2[i]=htop[i]=siz0[i]=siz1[i]=val[i]=0;
    }
    for(int i=1;i<=n;i++){
        t[i]=0;
    }
    initpre();
    ans=dtot=0;
}

void solve(){
    read(n,K);
    init();
    for(int i=1;i<=n;i++){
        read(t[i]);
    }
    for(int i=1;i<n;i++){
        read(e[i].u,e[i].v,e[i].w);
    }
    for(int i=1;i<=K;i++){
        int x;
        read(x);
        tagr[x]=1;
    }
    build();
    dfs1(dtot,0);
    dfs2(dtot,0,0);
    for(int i=1;i<=n;i++){
        if(!t[i]) ans+=calc0(i);
    }
    put(ans);
    for(int i=1;i<=n;i++){
        if(t[i]){
            put(ans-calc1(i)+calc0(i));
        }else{
            put(ans-calc0(i)+calc1(i));
        }
    }
}

signed main(){
    int T;
    read(T);
    while(T--){
        solve();
    }   
    return 0;
}