#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Query{
    int l,r,v;
};
int n,q,ans[MN];
vector<int> adj[MN],tmp[MN];
vector<Query> posk[MN],posr[MN],qryr[MN],qryk[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=max(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1;
        int ret=0;
        if(mid>=fl) ret=max(ret,query(ls,fl,fr));
        if(mid<fr) ret=max(ret,query(rs,fl,fr));
        return ret; 
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=max(t[p].val,k);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }
}sg[2],sgr;

struct DSU{
    int pre[MN];

    void init(int n){
        for(int i=1;i<=n;i++){
            pre[i]=i;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }
    
    // y is the merged element
    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        pre[ry]=rx;
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


namespace Tree{
    constexpr int ML=30;
    int dfn[MN],st[ML+2][MN],dep[MN],dtot;

    void dfs(int u,int pre){
        dfn[u]=++dtot;
        st[0][dfn[u]]=pre;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);
        }
    }

    int cmpdfn(int x,int y){
        return dfn[x]<dfn[y]?x:y;
    }

    void initst(){
        for(int i=1;i<=ML;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[i][j]=cmpdfn(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }

    int lca(int x,int y){
        if(x==y) return x;
        x=dfn[x],y=dfn[y];
        if(x>y) swap(x,y);
        int lg=__lg(y-x++);
        return cmpdfn(st[lg][x],st[lg][y-(1<<lg)+1]);
    }

}using namespace Tree;

void qinsert(int l,int r,int v){
    posr[r].push_back({l,r,v});
    posk[r-l+1].push_back({l,r,v});
}

void soldsu(int pos,int k){
    int l=pre.root(pos),r=suf.root(pos+1);
    qinsert(l,r,k);
    pre.merge(pos,pos+1);
    suf.merge(pos+1,pos);
}

void init(){
    pre.init(n);
    suf.init(n);
    sg[0].build(1,1,n);
    sg[1].build(1,1,n);
    sgr.build(1,1,n);
}

int main(){
    read(n);
    init();
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    initst();
    for(int i=1;i<n;i++){
        tmp[dep[lca(i,i+1)]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        qinsert(i,i,dep[i]);
    }
    for(int i=n;i>=1;i--){
        for(auto p:tmp[i]){
            soldsu(p,i);
        }
    }
    read(q);
    for(int i=1;i<=q;i++){
        int l,r,k;
        read(l,r,k);
        qryk[k].push_back({l,r,i});
        qryr[r].push_back({l,r,i});
    }
    for(int i=n;i>=1;i--){
        for(auto p:posk[i]){
            sg[0].modify(1,p.l,p.v);
            sg[1].modify(1,p.r,p.v);
        }
        for(auto p:qryk[i]){
            ans[p.v]=max({ans[p.v],sg[0].query(1,p.l,p.r-i+1),sg[1].query(1,p.l+i-1,p.r)});
        }
    }
    for(int i=n;i>=1;i--){
        for(auto p:posr[i]){
            sgr.modify(1,p.l,p.v);
        }
        for(auto p:qryr[i]){
            ans[p.v]=max(ans[p.v],sgr.query(1,1,p.l));
        }
    }
    for(int i=1;i<=q;i++) put(ans[i]);
    

    return 0;
}