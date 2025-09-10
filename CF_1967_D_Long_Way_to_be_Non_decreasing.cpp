#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,INF=1e9;
int pre[MN],n,m,a[MN],b[MN];
int del[MN];
vector<int> adj[MN];

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
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

namespace Tree{
    int dfn[MN],dtot,L[MN],R[MN],dep[MN];

    void dfs(int u){
        dfn[u]=++dtot;
        L[u]=dfn[u];
        for(auto v:adj[u]){
            dep[v]=dep[u]+1;
            dfs(v);
        }
        R[u]=dtot;
    }

    bool isin(int v, int u){
        return dfn[v]>=L[u]&&dfn[v]<=R[u];
    }
}using namespace Tree;

int dis(int x,int y){
    int rx=root(x),ry=root(y);
    if(rx!=ry) return INF;
    else if(isin(x,y)) return dep[x]-dep[y];
    else if(isin(b[del[rx]],y)) return dep[x]+1+dep[b[del[rx]]]-dep[y];
    return INF;
}

bool check(int k){
    int it=1;
    for(int i=1;i<=n;i++){
        while(it<=m&&dis(a[i],it)>k) it++;
        if(it>m) return 0;
    }
    return 1;
}

void init(){
    dtot=0;
    for(int i=1;i<=m;i++){
        pre[i]=i;
        adj[i].clear();
        del[i]=dep[i]=L[i]=R[i]=0;
    }
}

void solve(){
    read(n,m);
    init();
    for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=m;i++) read(b[i]);

    for(int i=1;i<=m;i++){
        int rx=root(i),ry=root(b[i]);
        if(rx==ry){
            del[rx]=i;
        }else{
            pre[rx]=ry; 
            adj[b[i]].push_back(i);
        }
    }
    for(int i=1;i<=m;i++)
        if(pre[i]==i) dfs(del[i]); 
    int l=0,r=m,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else l=mid+1;
    }
    put(ans);
}

int main(){
    int T;
    read(T);
    while(T--){
        solve();
    }
}
