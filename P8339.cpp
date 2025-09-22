#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,ML=30;
int n,m,t[MN],c[MN],ans[MN];
vector<int> adj[MN],G[MN],col[MN];
vector<pir> qry[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int y){
        while(x<=n){
            t[x]+=y;
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

    int query(int l,int r){
        return query(r)-query(l-1);
    }
}bit;

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
    int dfn[MN],st[ML+1][MN],dtot,dep[MN],siz[MN],hson[MN],htop[MN],fa[MN],id[MN];

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        siz[u]=1;
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
        dfn[u]=++dtot;
        st[0][dfn[u]]=fa[u];
        id[dfn[u]]=u;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;;
            dfs2(v,v);
        }
    }

    int cmpdfn(int x,int y){
        return dfn[x]<dfn[y]?x:y;
    }

    void initst(){
        for(int i=1;i<=ML;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[i][j]=cmpdfn(st[i-1][j],st[i-1][j+(1<<i-1)]);
            }
        }
    }

    //  If y is in the subtree of x,Return True otherwise False
    bool insub(int x,int y){
        return dfn[x]<=dfn[y]&&dfn[y]<dfn[x]+siz[x];
    }

    int jump(int x,int y){
        int lst=0;
        while(htop[x]!=htop[y]){
            lst=htop[x];
            x=fa[htop[x]];
        }
        if(x==y) return lst;
        return id[dfn[y]+1];
    }

    int lca(int x,int y){
        if(x==y) return x;
        x=dfn[x],y=dfn[y];
        if(x>y) swap(x,y);
        int lg=__lg(y-x++);
        return cmpdfn(st[lg][x],st[lg][y-(1<<lg)+1]);
    }
}using namespace Tree;

namespace VTree{
    int h[MN],vtot,st[MN],top;
    vector<int> clr;

    bool cmp(int x,int y){
        return dfn[x]<dfn[y];
    }

    void initvt(){
        for(auto p:clr){
            G[p].clear();
        }
        clr.clear();
        vtot=top=0;
    }

void getvt(){
    sort(h+1,h+1+vtot,cmp);
    top = 0;
    st[++top] = h[1];
    clr.push_back(h[1]);

    for(int i=2;i<=vtot;i++){
        int cur = h[i];
        int qlca = lca(st[top], cur);
        clr.push_back(cur);
        if(qlca == st[top]){
            st[++top] = cur;
            continue;
        }
        while(top > 1 && dep[st[top-1]] >= dep[qlca]){
            G[st[top-1]].push_back(st[top]);
            G[st[top]].push_back(st[top-1]);
            top--;
        }
        if(dep[st[top]] > dep[qlca]){
            G[qlca].push_back(st[top]);
            G[st[top]].push_back(qlca);
            clr.push_back(qlca);
            st[top] = qlca;
        }else if(st[top] != qlca){
            st[++top] = qlca;
        }
        st[++top] = cur;
    }
    while(top > 1){
        G[st[top-1]].push_back(st[top]);
        G[st[top]].push_back(st[top-1]);
        top--;
    }
}

}

namespace Solve{
    int S,nowc;
    vector<pir> chg[MN];

    void doqry(int fl,int fr,int x,int y){
        if(fl>fr||x>y) return;
        chg[fl].push_back(pir(x,1));
        chg[fl].push_back(pir(y+1,-1));
        chg[fr+1].push_back(pir(x,-1));
        chg[fr+1].push_back(pir(y+1,+1));
    }

    void insertqry(int x,int y){
        if(insub(x,y)){
            int z=jump(y,x);
            doqry(1,dfn[z]-1,dfn[y],dfn[y]+siz[y]-1);
            doqry(dfn[z]+siz[z],n,dfn[y],dfn[y]+siz[y]-1);
        }else if(insub(y,x)){
            int z=jump(x,y);
            doqry(dfn[x],dfn[x]+siz[x]-1,1,dfn[z]-1);
            doqry(dfn[x],dfn[x]+siz[x]-1,dfn[z]+siz[z],n);
        }else{
            doqry(dfn[x],dfn[x]+siz[x]-1,dfn[y],dfn[y]+siz[y]-1);
        }
    }

    void dfs(int u,int pre,int sum){
        if(sum<0) return;
        for(auto v:G[u]){
            if(v==pre) continue;
            if(!sum&&c[v]==nowc&&t[v]==2){
                insertqry(S,v);
                continue;
            }
            int nv=0;
            if(c[v]==nowc){
                nv+=(t[v]==1?1:-1);
            }
            dfs(v,u,sum+nv);
        }
    }

}

signed main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        read(t[i],c[i]);
        col[c[i]].push_back(i);
    }
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);       
    }
    dfs1(1,0);
    dfs2(1,1);
    initst();
    for(int i=1;i<=n;i++){
        if(!col[i].size()) continue;
        VTree::initvt();
        for(auto p:col[i]){
            VTree::h[++VTree::vtot]=p;
        }
        VTree::getvt();
        Solve::nowc=i;
        for(auto p:col[i]){
            if(c[p]==i&&t[p]==1){
                Solve::S=p;
                Solve::dfs(p,0,0);        
            }
        }
    } 
    for(int i=1;i<=m;i++){
        int u,v;
        read(u,v);
        qry[dfn[u]].push_back(pir(dfn[v],i));
    }
    for(int i=1;i<=n;i++){
        for(auto p:Solve::chg[i]){
            bit.modify(p.first,p.second);
        }
        for(auto p:qry[i]){
            ans[p.second]=bit.query(p.first);
        }
    }
    for(int i=1;i<=m;i++){
        put(ans[i]);
    }
    return 0;
}