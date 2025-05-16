#include <bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;
struct Query{
    int l,r,id,blk;
}qry[MN];
struct Node{
    int pre,nxt,id;
};
int n,m,q,len,ret,num[MN],ans[MN],a[MN],pre[MN],nxt[MN];
vector<int> adj[MN];
vector<Node> s;

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
    int tot,fa[MN],dep[MN],htop[MN],hson[MN],siz[MN],id[MN],dfn[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        siz[u]=1;
        dfn[u]=++tot;
        id[tot]=u;
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

    int dis(int x,int y){
        x=id[x];
        y=id[y];
        return dep[x]+dep[y]-2*dep[lca(x,y)];
    }

}
namespace t=Tree;

bool cmp(Query x,Query y){
    if(x.blk!=y.blk){
        return x.l<y.l;
    }
    return x.r>y.r;
}

void delr(int x){
    num[x]--;
    if(!num[x]){
        ret-=t::dis(pre[x],x);
        ret-=t::dis(x,nxt[x]);
        ret+=t::dis(pre[x],nxt[x]);
        pre[nxt[x]]=pre[x];
        nxt[pre[x]]=nxt[x];
    }
}

void dell(int x){
    s.push_back({pre[x],nxt[x],x});
    num[x]--;
    if(!num[x]){
        ret-=t::dis(pre[x],x);
        ret-=t::dis(x,nxt[x]);
        ret+=t::dis(pre[x],nxt[x]);
        pre[nxt[x]]=pre[x];
        nxt[pre[x]]=nxt[x];
    }
}

void solve(){
    int l=1,r=0;
    for(int i=1;i<=q;i++){
        if(qry[i].blk!=qry[i-1].blk){
            memset(num,0,sizeof(num));
            for(int j=(qry[i].blk-1)*len+1;j<=m;j++) num[t::dfn[a[j]]]++;
            int lst=0;
            for(int j=1;j<=n;j++){
                pre[j]=lst;
                if(num[j]) lst=j;
            }
            for(int j=1;j<=n;j++){
                if(!pre[j]) pre[j]=lst;
            }
            lst=0;
            for(int j=n;j>=1;j--){
                nxt[j]=lst;
                if(num[j]) lst=j;
            }
            for(int j=n;j>=1;j--){
                if(!nxt[j]) nxt[j]=lst;
            }
            ret=0;
            for(int j=1;j<=n;j++){
                if(num[j]) ret+=t::dis(pre[j],j);
            }
            r=m;
        }
        l=(qry[i].blk-1)*len+1;
        
        while(r>qry[i].r) delr(t::dfn[a[r--]]);
        int now=ret;
        while(l<qry[i].l) dell(t::dfn[a[l++]]);
        ans[qry[i].id]=ret/2+1;
        ret=now;
        while(!s.empty()){
            Node tmp=s.back();
            s.pop_back();
            if(!num[tmp.id]) nxt[tmp.pre]=tmp.id,pre[tmp.nxt]=tmp.id;
            num[tmp.id]++;
        }
    }
}

int main(){
    read(n);
    read(m);
    read(q);
    len=sqrt(m);
    for(int i=1;i<n;i++){
        int u,v;
        read(u);
        read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    t::dfs1(1,0);
    t::dfs2(1,1);
    for(int i=1;i<=m;i++){
        read(a[i]);
    }
    for(int i=1;i<=q;i++){
        read(qry[i].l);
        read(qry[i].r);
        qry[i].id=i;
        qry[i].blk=(qry[i].l-1)/len+1;
    }
    sort(qry+1,qry+1+q,cmp);
    solve();
    for(int i=1;i<=q;i++){
        put(ans[i]);
    }
    return 0;
}
