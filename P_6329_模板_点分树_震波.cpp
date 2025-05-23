#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e6+15;
constexpr int INF=1e9;
int n,m,a[MN];
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
#define ls t[p].lson
#define rs t[p].rson
    struct{
        int lson,rson,val;
    }t[MN];
    int tot,rt[MN];
    
    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void update(int &p,int l,int r,int pos,int k){
        if(!p) p=++tot;
        if(l==r){
            t[p].val+=k;
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) update(ls,l,mid,pos,k);
        else update(rs,mid+1,r,pos,k);
        pushup(p);
    }

    int query(int p,int l,int r,int fl,int fr){
        if(!p) return 0;
        if(l>=fl&&r<=fr) return t[p].val;
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) ret+=query(ls,l,mid,fl,fr);
        if(mid<fr) ret+=query(rs,mid+1,r,fl,fr);
        return ret;
    }

#undef ls
#undef rs
}t1,t2;

struct getrt{
    int siz[MN],dfa[MN],maxp[MN],rt;
    bool vis[MN];

    void findrt(int u,int pre,int tot){
        siz[u]=1;
        maxp[u]=0;
        for(auto v:adj[u]){
            if(v==pre||vis[v]) continue;
            findrt(v,u,tot);
            maxp[u]=max(maxp[u],siz[v]);
            siz[u]+=siz[v];
        }
        maxp[u]=max(maxp[u],tot-siz[u]);
        if(maxp[u]<maxp[rt]) rt=u;
    }

    void getdft(int u,int tot){
        vis[u]=1;
        for(auto v:adj[u]){
            if(vis[v]) continue;
            rt=0;
            int sz=(siz[v]<siz[u])?siz[u]:(tot-siz[u]);
            findrt(v,u,sz);
            dfa[rt]=u;
            getdft(rt,tot);
        }
    }

}gr;

namespace Tree{
    int htop[MN],hson[MN],dep[MN],siz[MN],fa[MN],dfn[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
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
            if(v==fa[u]||v==hson[u]) continue;
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

    int getdis(int x,int y){
        return dep[x]+dep[y]-dep[lca(x,y)]*2;
    }

}
using namespace Tree;

void modify(int x,int k){
    int cur=x;
    while(cur){
        t1.update(t1.rt[cur],0,n-1,getdis(cur,x),k);
        if(gr.dfa[cur]) t2.update(t2.rt[cur],0,n-1,getdis(gr.dfa[cur],x),k);
        cur=gr.dfa[cur];
    }
}

int query(int x,int k){
    int cur=x,pre=0,ret=0;
    while(cur){
        if(getdis(cur,x)>k){
            pre=cur;
            cur=gr.dfa[cur];
            continue;
        }
        ret+=t1.query(t1.rt[cur],0,n-1,0,k-getdis(cur,x));
        if(pre) ret-=t2.query(t2.rt[pre],0,n-1,0,k-getdis(cur,x));
        pre=cur,cur=gr.dfa[cur];
    }
    return ret;
}

signed main(){
    // freopen("dp.out","r",stdin);
    // freopen("ans.out","w",stdout);
    read(n,m);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    gr.maxp[0]=INF;
    gr.rt=0;
    gr.findrt(1,0,n);
    gr.getdft(gr.rt,n);
    // for(int i=1;i<=n;i++) cerr<<gr.dfa[i]<<" ";
    for(int i=1;i<=n;i++) modify(i,a[i]);

    int ans=0;
    while(m--){
        int op,x,y;
        read(op,x,y);
        x^=ans;
        y^=ans;
        if(op==0){
            ans=query(x,y);
            put(ans);
        }else{
            modify(x,y-a[x]);
            a[x]=y;
        }
    }
    return 0;
}
