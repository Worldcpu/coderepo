#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
constexpr int MN=5e6+15;
struct Edge{
    int v,id;
};
int n,a[MN],dtot,dg[MN],etot,dcnt;
vector<int> avct;
vector<Edge> adj[MN];
gp_hash_table<int,int> mp;
unordered_map<int,bool> viss;

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

namespace Euler{
    int cur[MN];
    bool vise[MN],visd[MN];

    void dfs(int u){
        if(!visd[u]){
            visd[u]=1;
            dcnt+=(u<=n);
        }
        while(cur[u]<adj[u].size()){
            auto e=adj[u][cur[u]++];
            if(!vise[e.id]){
                vise[e.id]=1;
                dfs(e.v);
            }
        }
        avct.push_back(u);
    }

    void init(){
        for(int i=1;i<=etot;i++) vise[i]=0;
        for(int i=0;i<=dtot;i++){
            dg[i]=0;
            cur[i]=0;
            visd[i]=0;
            adj[i].clear();
        }
    }
}

void cinit(int k){
    Euler::init();
    mp.clear();
    avct.clear();
    dtot=n,etot=dcnt=0;
    for(int i=0;i<(1<<k);i++){
        mp[i]=++dtot;
    }
    
}

bool check(int k){
    cinit(k);
    for(int i=1;i<=n;i++){
        int v=a[i*2-1]%(1<<k);
        adj[mp[v]].push_back({i,++etot});
        adj[i].push_back({mp[v],etot});
        dg[mp[v]]++,dg[i]++;
        v=a[i*2]%(1<<k);
        adj[mp[v]].push_back({i,++etot});
        adj[i].push_back({mp[v],etot});
        dg[mp[v]]++,dg[i]++;
    }
    for(int i=1;i<=dtot;i++){
        if(dg[i]&1) return 0;
    }
    Euler::dfs(1);
    return (dcnt==n);
}

int main(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[2*i-1],a[2*i]);
    }
    int l=0,r=20,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    put(ans);
    check(ans);
    int lst=0;
    for(auto p:avct){
        if(p<=n){
            if(viss[p]) continue;
            viss[p]=1;
            if(!lst){
                put(2*p-1,0);
                put(2*p,0);
                lst=2*p;
            }else{
                if((a[lst]^a[2*p-1])%(1<<ans)==0){
                    put(2*p-1,0);
                    put(2*p,0);
                    lst=2*p;
                }else put(2*p,0),put(2*p-1,0),lst=2*p-1;
            }
        }
    }
    return 0;
}