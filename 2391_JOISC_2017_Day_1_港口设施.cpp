#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15,MOD=1e9+7;
int pre[MN],n,bel[MN],nxt[MN],col[MN],L[MN],a[MN],tot,ctot;
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

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int root(int x){
    if(pre[x]==x) return pre[x];
    return pre[x]=root(pre[x]);
}

void initpre(){
    memset(col,-1,sizeof(col));
    for(int i=0;i<MN;i++) pre[i]=nxt[i]=i;
}

bool dfs(int u){
    for(auto v:adj[u]){
        if(~col[v]){
            if(col[v]==col[u]) return 0;
            continue;
        }
        col[v]=col[u]^1;
        if(!dfs(v)) return 0;
    }
    return 1;
}

signed main(){
    initpre();
    read(n);
    for(int i=1;i<=n;i++){
        int x,y;
        read(x,y);
        bel[x]=bel[y]=i;
    }
    for(int i=1;i<=2*n;i++){
        int u=bel[i];
        if(!L[u]){
            a[++tot]=u;
            L[u]=tot;
            continue;
        }
        for(int j=pre[L[u]]=root(L[u]+1);j<=tot;){
            adj[a[j]].push_back(u);
            adj[u].push_back(a[j]);
            int nxtt=root(nxt[j]+1);
            nxt[j]=tot;
            j=nxtt;
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]==-1){
            ctot++;
            col[i]=0;
            if(!dfs(i)){
                cout<<0;
                return 0;
            }           
        }
    }
    cerr<<ctot<<'\n';
    cout<<ksm(2,ctot);
    return 0;
}