#include<bits/stdc++.h>
#include<bits/extc++.h>
#define ull unsigned long long
using namespace std;
using namespace __gnu_pbds;
constexpr ull base=13131,prime=114514191;
constexpr int MN=5e5+15;
int n,m,q,rt,a[MN];
ull pw[MN],hsh[MN],now;
gp_hash_table<ull,int> mp;
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

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r;
        ull hsh;
    }t[MN<<2];

    void pushup(int p){
        t[p].hsh=t[ls].hsh*pw[t[rs].r-t[rs].l+1]+t[rs].hsh;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].hsh=a[l]+prime;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modfiy(int p,int pos,ull k){
        if(t[p].l==t[p].r){
            t[p].hsh=k+prime;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modfiy(ls,pos,k);
        else modfiy(rs,pos,k);
        pushup(p);
    }

    ull getans(int p){
        if(t[p].l==t[p].r) return t[p].l;
        int mid=(t[p].l+t[p].r)>>1;
        ull x=now*pw[mid-t[p].l+1]+t[ls].hsh;
        if(mp.find(x)==mp.end()) return getans(ls);
        now=x;
        return getans(rs);
    }

    ull query(int p,int fl,int fr,bool &isfind){
        if(t[p].l>=fl&&t[p].r<=fr){
            ull x=now*pw[t[p].r-t[p].l+1]+t[p].hsh;
            if(mp.find(x)==mp.end()){
                isfind=1;
                return getans(p);
            }
            now=x;
            return 0;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr,isfind);
        if(mid>=fr) return query(ls,fl,fr,isfind);
        ull ret=query(ls,fl,fr,isfind);
        return isfind?ret:query(rs,fl,fr,isfind);
    }

#undef ls
#undef rs
}t;

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*base;
}

void dfs(int u,int pre){
    mp[hsh[u]]=u;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
        if(v==pre) continue;
        hsh[v]=hsh[u]*base+i+1+prime;
        dfs(v,u);
    }
}



int main(){
    init();
    read(n,m,q);
    for(int i=1;i<=n;i++){
        int fa;
        read(fa);
        if(!fa) rt=i;
        else adj[fa].push_back(i);
    }
    for(int i=1;i<=m;i++){
        read(a[i]);
    }
    for(int i=1;i<=n;i++){
        sort(adj[i].begin(),adj[i].end());
    }
    dfs(rt,0);
    t.build(1,1,m);
    while(q--){
        int op,x,l,r;
        read(op);
        if(op==1){
            read(x,l,r);
            now=hsh[x];
            bool awa=0;
            t.query(1,l,r,awa);
            put(mp[now]);
        }else{
            read(l,x);
            t.modfiy(1,l,x);
        }
    }
    return 0;
}
