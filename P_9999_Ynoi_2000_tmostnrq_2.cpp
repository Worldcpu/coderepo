#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e6+15;
struct FHQNode{
    int lson,rson,tag,siz,val,dat,sum,fa;
}t[MN];
int n,n0,m,a[MN],ans[MN];
vector<int> adj[MN];
vector<pir> qry[2][MN];

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

struct DSU{
    int pre[MN];

    DSU(){
        for(int i=1;i<MN;i++) pre[i]=i;
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        return pre[x]=root(pre[x]);
    }

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        pre[ry]=root(rx);
    }

}dsu;

struct FHQTreap{
#define ls t[p].lson
#define rs t[p].rson

    int tot;

    FHQTreap(){
        t[0].val=-1;
        srand(time(0));
    }

    int newnode(int k){
        t[++tot].val=k;
        t[tot].dat=rand();
        t[tot].lson=t[tot].rson=t[tot].fa=0;
        t[tot].siz=t[tot].sum=1;
        t[tot].tag=0;
        return tot;
    }

    void pushup(int p){
        t[p].siz=t[ls].siz+t[rs].siz+t[p].sum;
        if(ls) t[ls].fa=p;
        if(rs) t[rs].fa=p;
        t[p].fa=0;
    }

    void pushdown(int p){
        if(t[p].tag){
            if(ls){
                t[ls].tag+=t[p].tag;
                t[ls].val+=t[p].tag;
            }
            if(rs){
                t[rs].tag+=t[p].tag;
                t[rs].val+=t[p].tag;
            }
            t[p].tag=0;
        }
    }

    void splitval(int p,int k,int &x,int &y){
        if(!p){
            x=y=0;
            return;
        }
        pushdown(p);
        if(t[p].val<=k){
            x=p;
            splitval(rs,k,rs,y);
        }else{
            y=p;
            splitval(ls,k,x,ls);
        }
        pushup(p);
    }

    void splitsiz(int p,int k,int &x,int &y){
        if(!p){
            x=y=0;
            return;
        }
        pushdown(p);
        if(t[ls].siz+t[p].sum<=k){
            x=p;
            splitsiz(rs,k-t[ls].siz-t[p].sum,rs,y);
        }else{
            y=p;
            splitsiz(ls,k,x,ls);
        }
        pushup(p);
    }

    int merge(int x,int y){
        if(!x||!y){
            return x+y;
        }
        if(t[x].dat<t[y].dat){
            pushdown(x);
            t[x].rson=merge(t[x].rson,y);
            pushup(x);
            return x;
        }else{
            pushdown(y);
            t[y].lson=merge(x,t[y].lson);
            pushup(y);
            return y;
        }
    }

    int getl(int p){
        while(ls){
            pushdown(p);
            p=ls;
        }
        return p;
    }

    int getr(int p){
        while(rs){
            pushdown(p);
            p=rs;
        }
        return p;
    }

#undef ls 
#undef rs
}fhq;

namespace Tree{
    int dep[MN],hson[MN],siz[MN],htop[MN],fa[MN];
    vector<int> lst[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        siz[u]=1;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        lst[ltop].emplace_back(u);
        if(!hson[u]) 
            return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }
}

namespace sol{
    using namespace Tree;
    int rt[MN],rttag[MN],rts[MN],frt[MN],st[MN],flg,top,tag;
    set<pir> s;

    void chg(int x){
        if(!rt[x]){
            rttag[x]=tag;
            return;
        }
        t[rt[x]].val-=(tag-rttag[x]);
        t[rt[x]].tag-=(tag-rttag[x]);
        rttag[x]=tag;
    }

    void sera(int x){
        chg(x);
        if(!rt[x]||rts[x]==-1) return;
        frt[rt[x]]=0;
        s.erase(pir(rts[x],x));
        rts[x]=-1;
        frt[rt[x]]=x;
    }

    void sins(int x){
        chg(x);
        if(!rt[x]) return;
        frt[rt[x]]=0;
        int tmp=fhq.getl(rt[x]);
        s.insert(pir(t[tmp].val+tag+flg,x));
        rts[x]=t[tmp].val+tag+flg;
        frt[rt[x]]=x;
    }

    void insert(int x,int k){
        chg(x);
        int tmp=0,tmp1=0;
        frt[rt[x]]=0;
        sera(x);
        fhq.splitval(rt[x],t[k].val,rt[x],tmp);
        tmp1=fhq.getr(rt[x]);
        if(t[tmp1].val==t[k].val){
            fhq.splitsiz(rt[x],t[rt[x]].siz-t[tmp1].sum,rt[x],tmp1);
            t[tmp1].sum+=t[k].sum;
            t[tmp1].siz+=t[k].sum;
            dsu.merge(tmp1,k);
            rt[x]=fhq.merge(rt[x],tmp1);
        }
        else rt[x]=fhq.merge(rt[x],k);
        rt[x]=fhq.merge(rt[x],tmp);
        sins(x);
        frt[rt[x]]=x;
    }

    int erase(int x,int sum,int op){
        chg(x);
        frt[rt[x]]=0;
        int tmp=0,tmp1=0;
        sera(x);
        fhq.splitsiz(rt[x],sum,rt[x],tmp);
        fhq.splitsiz(tmp,t[fhq.getl(tmp)].sum,tmp,tmp1);
        if(op){
            t[tmp].sum--;
            if(t[tmp].sum) 
                tmp1=fhq.merge(tmp,tmp1);
        }
        rt[x]=fhq.merge(rt[x],tmp1);
        sins(x);
        frt[rt[x]]=x;
        return tmp;
    }

    int add(int x){
        int p=fhq.newnode(dep[x]-dep[htop[x]]);
        insert(htop[x],p);
        return p;
    }

    int del(int x){
        top=0;
        int p=x,sum=t[t[x].lson].siz,tmp=0;
        while(p){
            st[++top]=p;
            p=t[p].fa;
        }
        p=st[top];
        tmp=frt[p];
        while(p!=x){
            if(t[p].rson==st[top]) 
                sum+=t[t[p].lson].siz+t[p].sum;
            p=st[top--];
        }
        erase(tmp,sum,1);
        return lst[tmp][t[x].val];
    }

    void solve(int u){
        int x=u,lst=0;
        flg=1;
        while(x){
            int tx=htop[x],val=dep[x]-dep[tx]-(u==x),tmp=0,tmp1=0;
            sera(tx);
            frt[rt[tx]]=0;
            chg(tx);
            fhq.splitval(rt[tx],val,rt[tx],tmp);
            if(rt[tx]){
                t[rt[tx]].val++;
                t[rt[tx]].tag++;
            }
            if(u==x){
                fhq.splitval(tmp,val+1,tmp1,tmp);
            }
            if(tmp){
                t[tmp].val--;
                t[tmp].tag--;
            }
            if(u==x) 
                tmp=fhq.merge(tmp1,tmp);
            tmp1=fhq.getr(rt[tx]);
            while(t[tmp1].val>val&&u!=x){
                erase(tx,t[rt[tx]].siz-t[tmp1].sum,0);
                t[tmp1].val=t[tmp1].tag=0;
                t[tmp1].siz=t[tmp1].sum;
                insert(lst,tmp1);
                tmp1=fhq.getr(rt[tx]);
            }
            rt[tx]=fhq.merge(rt[tx],tmp);
            sins(tx);
            frt[rt[tx]]=tx;
            lst=tx;
            x=fa[tx];
        }
        flg=0;
        x=u;
        while(x){
            rttag[htop[x]]=tag+1;
            x=fa[htop[x]];
        }
        tag++;
        while(!s.empty()){
            auto it=s.begin();
            if(it->first>=tag) break;
            int tmp=erase(it->second,0,0);
            t[tmp].val=dep[fa[it->second]]-dep[htop[fa[it->second]]];
            t[tmp].tag=0;
            t[tmp].siz=t[tmp].sum;
            insert(htop[fa[it->second]],tmp);
        }
    }
}
signed main(){
    freopen("dp.out","r",stdin);
    read(n,n0,m);
    for(int i=2;i<=n;i++){
        read(Tree::fa[i]);
        adj[Tree::fa[i]].push_back(i);
    }
    for(int i=1;i<=n0;i++){
        read(a[i]);
    }
    for(int i=1;i<=m;i++){
        int l,r,x;
        read(l,r,x);
        qry[0][l].push_back(pir(x,i));
        qry[1][r].push_back(pir(x,i));
    }
    Tree::dfs1(1,0);
    Tree::dfs2(1,1);
    for(int i=1;i<=n0;i++){
        for(auto v:qry[0][i]){
            ans[v.second]=sol::add(v.first);
        }
        sol::solve(a[i]);
        for(auto v:qry[1][i]){
            ans[v.second]=sol::del(dsu.root(ans[v.second]));
        }
    }
    for(int i=1;i<=m;i++){
        put(ans[i]);
    }
    return 0;
}