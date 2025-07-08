#include<bits/stdc++.h>
#define il inline
#define pir pair<int,int>
using namespace std;
constexpr int MN=4e5+15;
int n,q,fa[MN],pos[MN],ans[MN];
string s;
vector<int> adj[MN];
vector<pir> que[MN];

struct SegmentMerge{
#define ls t[p].lson
#define rs t[p].rson

    struct Node{
        int lson,rson;
    }t[MN*20];
    int tot,rt[MN];

    il void modify(int &p,int l,int r,int pos){
        if(!p) p=++tot;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,l,mid,pos);
        else modify(rs,mid+1,r,pos);
    }

    il int merge(int x,int y,int l,int r){
        if(!x||!y) return x|y;
        int p=++tot;
        if(l==r) return p;
        int mid=(l+r)>>1;
        ls=merge(t[x].lson,t[y].lson,l,mid);
        rs=merge(t[x].rson,t[y].rson,mid+1,r);
        return p;
    }

    il int query(int p,int l,int r,int pos){
        if(l>pos||!p) return -1;
        if(l==r) return l;
        int mid=(l+r)>>1;
        int ret=query(rs,mid+1,r,pos);
        if(~ret) return ret;
        else return query(ls,l,mid,pos);
    }


#undef ls
#undef rs
}sgm;

struct SegmentTree {
    static const int Siz = MN * (4) ;
    #define ls x<<1
    #define rs x<<1|1
    #define mid ((l+r)>>1)    

    int ch[Siz] ;

    SegmentTree () {
        memset (ch , -1 , sizeof ch) ;
    }

    inline void update (int x,int l,int r,int L,int R,int c) {
        if (L > R || L > r || l > R)
            return ;
        if (L <= l && r <= R)  
            return ch[x]=max(ch[x],c),void() ;
        update (ls , l , mid , L , R , c) ;
        update (rs , mid + 1 , r , L , R , c) ;
    }
    
    inline void recall (int x,int l,int r,int L,int R,int c) {
        if (L > R || L > r || l > R)
            return ;
        if (L <= l && r <= R)
            return ch[x] = -1 , void (); 
        recall (ls , l , mid , L , R , c) ;
        recall (rs , mid + 1 , r , L , R , c) ;
    }

    inline int query (int x,int l,int r,int p) {
        if (l == r) 
            return ch[x] ;
        return p <= mid ? 
                std :: max (query (ls , l , mid , p) , ch[x]) :
                std :: max (query (rs , mid + 1 , r , p) , ch[x]) ; 
    }

    #undef ls
    #undef rs
    #undef mid 
}sg;  

struct SAM{// 1-based
    int nxt[MN][26],len[MN],tot,lst;

    void init(){
        tot=lst=1;
    }

    inline void expand(int c){
        int cur=++tot;
        len[cur]=len[lst]+1;
        int p=lst;
        while(p&&!nxt[p][c]) nxt[p][c]=cur,p=fa[p];
        if(!p){
            fa[cur]=1;
        }else{
            int q=nxt[p][c];
            if(len[q]==len[p]+1){
                fa[cur]=q;
            }else{
                int nq=++tot;
                len[nq]=len[p]+1,fa[nq]=fa[q];
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
                fa[q]=fa[cur]=nq;
                while(p&&nxt[p][c]==q){
                    nxt[p][c]=nq;
                    p=fa[p];
                }
            }
        }
        lst=cur;
    }

    inline void inittree(){
        for(int i=2;i<=tot;i++) adj[fa[i]].push_back(i);
    }

}sam;

namespace Tree{
    int siz[MN],hson[MN],htop[MN],hpos[MN],L[MN],R[MN],dfn[MN],pre[22][MN],dtot;
    vector<int> lk[MN];

    void dfs1(int u){
        siz[u]=1;
        pre[0][u]=fa[u];
        for(int i=1;i<=20;i++){
            pre[i][u]=pre[i-1][pre[i-1][u]];
        }
        for(auto v:adj[u]){
            dfs1(v);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
            sgm.rt[u]=sgm.merge(sgm.rt[u],sgm.rt[v],1,n);
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        lk[ltop].push_back(u);
        L[u]=++dtot;
        dfn[dtot]=u;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==hson[u]) continue;
            dfs2(v,v);
        }
        R[u]=dtot;
    }

}
using namespace Tree;

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

inline void build(){
    for(int i=1;i<=n;i++){
        hpos[pos[i]]=i;
        sgm.modify(sgm.rt[pos[i]],1,n,i);
    }
    dfs1(1);
    dfs2(1,1);
}

inline void getquery(int u,int l,int r,int id){
    int now=u;
    for(int i=20;i>=0;i--){
        if(sam.len[pre[i][now]]>=r-l+1){
            now=pre[i][now];
        }
    }
    now=fa[now];
    while(now){
        int ret=sgm.query(sgm.rt[now],1,n,l+sam.len[now]-1);
        if(ret>=l)
            ans[id]=max(ans[id],ret-l+1);
        que[now].push_back(pir(l,id));
        now=fa[htop[now]];
    }
}

inline void solve(vector<int> &lk){
    for(auto u:lk){
        int length=sam.len[u];
        if(hpos[u]){
            sg.update(1,1,n,hpos[u]-length+1,hpos[u],hpos[u]);
        }
        for(auto v:adj[u]){
            if(v==hson[u]) continue;
            for(int i=L[v];i<=R[v];i++){
                int g=hpos[dfn[i]];
                if(g) sg.update(1,1,n,g-length+1,g,g);
            }
        }
        for(auto p:que[u]){
            ans[p.second]=max(ans[p.second],sg.query(1,1,n,p.first)-p.first+1);
        }
    }
    for(auto u:lk){
        int length=sam.len[u];
        if(hpos[u]){
            sg.recall(1,1,n,hpos[u]-length+1,hpos[u],hpos[u]);
        }
        for(auto v:adj[u]){
            if(v==hson[u]) continue;
            for(int i=L[v];i<=R[v];i++){
                int g=hpos[dfn[i]];
                if(g) sg.recall(1,1,n,g-length+1,g,g);
            }
        }
    }
}



signed main(){
    read(s);
    sam.init();
    for(auto c:s){
        sam.expand(c-'a');
        pos[++n]=sam.lst;
    }
    sam.inittree();
    build();
    read(q);
    for(int i=1;i<=q;i++){
        int l,r;
        read(l,r);
        getquery(pos[r],l,r,i);
    }

    for(int i=1;i<=sam.tot;i++){
        if(htop[i]==i) solve(lk[i]);
    }
    for(int i=1;i<=q;i++) put(ans[i]);

    return 0;
}
