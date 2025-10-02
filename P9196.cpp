#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15;
struct Query{
    int l,r,op,id;

    Query(int ll=0,int rr=0,int opp=0,int idd=0){
        l=ll,r=rr,op=opp,id=idd;
    }
};
int n,m,ans[MN];
string inst[MN];
vector<int> pos[MN];
vector<Query> qry[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }
}bit;

struct Trie{
    int t[MN][4],tot=1,end[MN],dfn[MN],dtot,siz[MN],id[MN];

    int getid(char ch){
        if(ch=='A') return 0;
        if(ch=='C') return 1;
        if(ch=='U') return 2;
        return 3;
    }

    void insert(string st){
        int p=1;
        for(auto c:st){
            int k=getid(c);
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[p]++;
    }

    int find(string st){
        int p=1;
        for(auto c:st){
            int k=getid(c);
            if(!t[p][k]) return -1;
            p=t[p][k];
        }
        return p;
    }

    void dfs(int u){
        siz[u]=1;
        dfn[u]=++dtot;
        id[dtot]=u;
        for(int i=0;i<4;i++){
            if(t[u][i]){
                dfs(t[u][i]);
                siz[u]+=siz[t[u][i]];
            }
        }
    }
}pre,suf;

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

bool cmp(Query x,Query y){
    return (x.l==y.l?x.r<y.r:x.l<y.l);
}

signed main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        read(inst[i]);
        pre.insert(inst[i]);
        reverse(inst[i].begin(),inst[i].end());
        suf.insert(inst[i]);
        reverse(inst[i].begin(),inst[i].end());
    }
    pre.dfs(1);
    suf.dfs(1);
    for(int i=1;i<=n;i++){
        int x,y;
        x=pre.find(inst[i]);
        reverse(inst[i].begin(),inst[i].end());
        y=suf.find(inst[i]);
        x=pre.dfn[x],y=suf.dfn[y];
        pos[x].push_back(y);
    }
    for(int i=1;i<=m;i++){
        int x,y;
        string prest,sufst;
        read(prest,sufst);
        reverse(sufst.begin(),sufst.end());
        x=pre.find(prest);
        y=suf.find(sufst);
        if(x==-1||y==-1) continue;
        qry[pre.dfn[x]-1].push_back(Query(pre.dfn[x]-1,suf.dfn[y]-1,1,i));
        qry[pre.dfn[x]-1].push_back(Query(pre.dfn[x]-1,suf.dfn[y]+suf.siz[y]-1,-1,i));
        qry[pre.dfn[x]+pre.siz[x]-1].push_back(Query(pre.dfn[x]+pre.siz[x]-1,suf.dfn[y]-1,-1,i));
        qry[pre.dfn[x]+pre.siz[x]-1].push_back(Query(pre.dfn[x]+pre.siz[x]-1,suf.dfn[y]+suf.siz[y]-1,1,i));
    }
    for(int i=1;i<=pre.dtot;i++){
        for(auto p:pos[i]){
            bit.modify(p,1);
        }
        for(auto p:qry[i]){
            ans[p.id]+=p.op*bit.query(p.r);
        }
    }
    for(int i=1;i<=m;i++){
        put(ans[i]);
    }
    return 0;
}