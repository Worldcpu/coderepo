#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
struct Edge{
    int u,v,w;
}e[MN];
struct Node{
    int h,id;
}hh[MN];
int n,m,q,h[MN],pre[MN],dtot,val[MN],rt[MN];
bool vis[MN];
vector<int> adj[MN];

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson,cnt;
    }t[MN*50];
    int tot;

    void build(int &p,int l,int r){
        p=++tot;
        t[p].cnt=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modify(int &p,int lst,int l,int r,int pos){
        p=++tot;
        t[p]=t[lst];
        t[p].cnt++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,t[lst].lson,l,mid,pos);
        else modify(rs,t[lst].rson,mid+1,r,pos);
    }

    int query(int x,int y,int l,int r,int k){
        if(l==r){
            if(k-(t[x].cnt-t[y].cnt)==0) return l;
            return 0;
        }
        int mid=(l+r)>>1,rkid=(t[t[x].rson].cnt-t[t[y].rson].cnt);
        if(rkid>=k) return query(t[x].rson,t[y].rson,mid+1,r,k);
        else return query(t[x].lson,t[y].lson,l,mid,k-rkid);
    }
}sg;

namespace Tree{
    int fa[33][MN],L[MN],R[MN],ftot,lf[MN];

    void dfs1(int u,int pre){
        fa[0][u]=pre;
        for(int i=1;i<=30;i++){
            fa[i][u]=fa[i-1][fa[i-1][u]];
        }
        L[u]=ftot;
        if(adj[u].empty()){
            lf[++ftot]=u;
            R[u]=ftot;
            return;
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
        }
        R[u]=ftot;
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

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void buildkru(){
    dtot=n;
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru!=rv){
            dtot++;
            adj[dtot].push_back(ru);
            adj[dtot].push_back(rv);
            val[dtot]=e[i].w;
            pre[ru]=pre[rv]=dtot;
            if(dtot==2*n-1) break;
        }
    }
    for(int i=1;i<=n;i++){
        int rtt=root(i);
        if(!vis[rtt]){
            dfs1(rtt,0);
            vis[rtt]=1;
        }
    }
}

void initpre(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
    }
}

int findfa(int x,int k){
    int now=x;
    for(int i=30;i>=0;i--){
        if(val[fa[i][now]]<=k) now=fa[i][now];
    }
    return now;
}

bool cmpn(Node x,Node y){
    return x.h<y.h;
}

bool cmpe(Edge x,Edge y){
    return x.w<y.w;
}

int main(){
    initpre();
    read(n,m,q);
    for(int i=1;i<=n;i++){
        read(hh[i].h);
        hh[i].id=i;
    }
    sort(hh+1,hh+1+n,cmpn);
    for(int i=1;i<=n;i++){
        h[hh[i].id]=i;
    }
    for(int i=1;i<=m;i++){
        read(e[i].u,e[i].v,e[i].w);
    }
    sort(e+1,e+1+m,cmpe);
    buildkru();
    sg.build(rt[0],1,n);
    for(int i=1;i<=ftot;i++){
        rt[i]=rt[i-1];
        sg.modify(rt[i],rt[i-1],1,n,h[lf[i]]);
    }
    hh[0].h=-1;
    val[0]=1e9+7;
    for(int i=1;i<=q;i++){
        int x,y,z;
        read(x,y,z);
        int rtt=findfa(x,y);
        int ans=sg.query(rt[R[rtt]],rt[L[rtt]],1,n,z);
        put(hh[ans].h);
    }
    return 0;
}