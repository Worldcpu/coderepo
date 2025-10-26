#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
constexpr int MV = 1000000000;
int rt[MN],n,m,val[MN];
string s[MN];
vector<int> adj[MN],G[MN],pos[MN];

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
    struct Node{
        int lson,rson,val;
    }t[MN*50];
    int tot;

    void modify(int &p,int lst,int l,int r,int pos){
        p=++tot;
        t[p]=t[lst];
        t[p].val++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=pos) modify(t[p].lson,t[lst].lson,l,mid,pos);
        else modify(t[p].rson,t[lst].rson,mid+1,r,pos);
    }

    int query(int x,int y,int l,int r,int fl,int fr){
        if(l>=fl&&r<=fr){
            return t[y].val-t[x].val;
        }
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) ret+=query(t[x].lson,t[y].lson,l,mid,fl,fr);
        if(mid<fr) ret+=query(t[x].rson,t[y].rson,mid+1,r,fl,fr);
        return ret;
    }
}sg;

struct ACAuto{
    int t[MN][26],tot=1,fail[MN],end[MN],tag[MN];

    void insert(string s,int id){
        int p=1;
        for(auto c:s){
            int k=c-'a';
            if(!t[p][k]) t[p][k]=++tot;
            p=t[p][k];
        }
        end[id]=p;
    }

    void build(){
        queue<int> q;
        fail[1]=0;
        for(int i=0;i<26;i++){
            if(t[1][i]){
                fail[t[1][i]] = 1;
                q.push(t[1][i]);
            } else {
                t[1][i] = 1;
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;i++){
                int v=t[u][i];
                if(v){
                    fail[v] = t[fail[u]][i];
                    q.push(v);
                } else {
                    t[u][i] = t[fail[u]][i];
                }
            }
        }
        for(int i=2;i<=tot;i++){
            adj[fail[i]].push_back(i);
        }
    }

}ac;

namespace Tree{
    int htop[MN],hson[MN],dfn[MN],dep[MN],siz[MN],fa[MN],dtot;

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        siz[u]=1;
        fa[u]=pre;
        rt[u]=rt[pre];
        for(auto p:pos[u]){
            sg.modify(rt[u],rt[u],1,MV,p);
        }
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(!hson[u]||siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        dfn[u]=++dtot;
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
}using namespace Tree;

namespace VTree{
    int h[MN],tmp[MN],vtot,ttot,st[MN],top;
    
    bool cmp(int x,int y){
        return dfn[x]<dfn[y];
    }

    void initvt(){
        for(int i=1;i<=ttot;i++){
            G[tmp[i]].clear();
            ac.tag[tmp[i]]=0;
        }
        ttot=vtot=top=0;
    }

    int getvt(){
        if(vtot==0) return 0;
        sort(h+1,h+1+vtot,cmp);
        int base=0;
        static int tmp2[MN];
        for(int i=1;i<=vtot;i++){
            if(base==0 || h[i]!=h[base]) tmp2[++base]=h[i];
        }
        int tlen = base;
        for(int i=1;i<tlen;i++){
            int l = lca(tmp2[i], tmp2[i+1]);
            tmp2[++base] = l;
        }
        sort(tmp2+1,tmp2+1+base,cmp);
        ttot=0;
        for(int i=1;i<=base;i++){
            if(ttot==0 || tmp2[i]!=tmp[ttot]) tmp[++ttot]=tmp2[i];
        }
        for(int i=1;i<=ttot;i++){
            G[tmp[i]].clear();
        }
        static int stk[MN];
        int top = 0;
        for(int i=1;i<=ttot;i++){
            int u = tmp[i];
            while(top>0 && !(dfn[stk[top]] <= dfn[u] && dfn[u] < dfn[stk[top]] + siz[stk[top]])) top--;
            if(top>0){
                G[stk[top]].push_back(u);
            }
            stk[++top] = u;
        }
        return tmp[1];
    }

    void acfind(string st){
        int p=1;
        for(auto c:st){
            int k=c-'a';
            p=ac.t[p][k];
            h[++vtot]=p;
            ac.tag[p]++;
        }
    }
}using namespace VTree;

void dfs3(int u,int pre){
    for(auto v:G[u]){
        if(v==pre) continue;
        dfs3(v,u);
        ac.tag[u]+=ac.tag[v];
    }
}

int dfs4(int u,int mid,int pre){
    int ret=0;
    for(auto v:G[u]){
        if(v==pre) continue;
        ret+=dfs4(v,mid,u);
        if(ac.tag[v]==0) continue; 
        int need = (mid-1 + ac.tag[v]) / ac.tag[v];
        if(need > MV) continue;
        ret += sg.query(rt[u],rt[v],1,MV,need,MV);
    }
    return ret;
}

signed main(){
    read(n,m);
    for(int i=1;i<=n;i++){
        read(s[i],val[i]);
        ac.insert(s[i],i);
        pos[ac.end[i]].push_back(val[i]);
    }
    ac.build();
    dfs1(1,0);
    dfs2(1,1);
    while(m--){
        string st;
        int x;
        read(st,x);
        initvt();
        acfind(st);
        int rt = getvt();
        if(rt==0){
            put(0);
            continue;
        }
        dfs3(rt,0);
        int l=1,r=1000000000,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(dfs4(rt,mid,0)>=x) l=mid+1,ans=mid;
            else r=mid-1;
        }
        put(ans);
    }
    return 0;
}
