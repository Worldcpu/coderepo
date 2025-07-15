#include<bits/stdc++.h>
#define ll long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e5+100,MB=100,MBL=500;
struct Query{
    int l,r,id;
    ll op;
}tqry[MN];
int n,m,rt,R[MN],tmp[MN],dg[MN],pos[MN],bl;
ll ans1,ans2,ans3[MN],sum[MN],cnt[MN],ans[MN];
bool vis[MN];
vector<int> adj[MN];
vector<Query> qry[MN];

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
    int siz[MN],fa[MN],dfn[MN],dtot;
    pir a[MN];
    
    void dfs1(int u,int pre){
        siz[u]=1;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
        }
    }

    void dfs2(int u,int pre){
        dfn[++dtot]=u;
        a[dtot]=pir(u,pre);
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs2(v,u);
        }
    }

}using namespace Tree;

bool cmpsiz(int x,int y){
    return siz[x]>siz[y];
}

bool cmpmd(Query x,Query y){
    if(pos[x.l]!=pos[y.l]) return pos[x.l]<pos[y.l];
    return (pos[x.l]&1)?x.r<y.r;
}

void add(int x,ll op){
    ans1+=1ll*1+cnt[x]*2*op;
    cnt[x]+=op;
    ans2+=op;
}

ll query(int x){
    return (x?(R[x]==x?sum[pos[x]]:sum[pos[x]-1]+cnt[x]):0);
}

void update(int x){
    for(int i=pos[x];i<=pos[n];i++){
        sum[i]++;
    }
    for(int i=x;i<=R[x];i++) cnt[i]++;
}

void solve1(int x){
    if(qry[x].empty()) return;
    int tmptot=0;
    for(auto v:adj[x]){
        if(v==fa[x]) continue;
        tmp[++tmptot]=v;
    }
    sort(tmp+1,tmp+1+tmptot,cmpsiz);
    dtot=0;
    for(int i=MB+1;i<=tmptot;i++){
        dfs2(tmp[i],tmp[i]);
        vis[tmp[i]]=1;
    }
    sort(a+1,a+1+dtot);
    sort(dfn+1,dfn+1+dtot);
    for(int i=0;i<qry[x].size();i++){
        int ql=lower_bound(dfn+1,dfn+1+dtot,qry[x][i].l)-dfn;
        int qr=upper_bound(dfn+1,dfn+1+dtot,qry[x][i].r)-dfn-1;
        tqry[i+1]={ql,qr,qry[x][i].id};
    }
    int l=1,r=0,bl=dtot/sqrt(qry[x].size())+1;
    for(int i=1;i<=dtot;i++){
        pos[i]=(i+bl-1)/bl;
    }
    sort(tqry+1,tqry+1+qry[x].size(),cmpmd);
    ans1=ans2=0;
    for(int i=1;i<=qry[x].size();i++){
        if(tqry[i].l>dtot||tqry[i].r<1) continue;
        while(l<tqry[i].l) add(a[l++].second,-1);
        while(l>tqry[i].l) add(a[--l].second,1);
        while(r<tqry[i].r) add(a[++r].second,1);
        while(r>tqry[i].r) add(a[r--].second,-1);
        ans[tqry[i].id]-=ans1;
        ans3[tqry[i].id]+=ans2;
    }
}

void solve2(int x){
    if(!vis[x]&&fa[x]&&!qry[fa[x]].empty()){
        for(int i=0;i<qry[fa[x]].size();i++){
            qry[fa[x]][i].op=query(qry[fa[x]][i].r)-query(qry[fa[x]][i].l-1);
        }
    }
    update(x);
    for(auto v:adj[x]){
        if(v==fa[x]) continue;
        solve2(v);
    }
    if(!vis[x]&&fa[x]&&!qry[fa[x]].empty()){
        for(int i=0;i<qry[fa[x]].size();i++){
            ll qwq=query(qry[fa[x]][i].r)-query(qry[fa[x]][i].l-1)-qry[fa[x]][i].op;
            ans[qry[fa[x]][i].id]-=qwq*qwq;
            ans3[qry[fa[x]][i].id]+=qwq;
        }
    }
    for(int i=0;i<qry[x].size();i++){
        if(qry[x][i].l<=x&&x<=qry[x][i].r){
            ans[qry[x][i].id]+=ans3[qry[x][i].id]*2;
        }
    }
}

signed main(){
    read(n,m,rt);
    for(int i=1;i<n;i++){
        int u,v;
        read(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        dg[u]++,dg[v]++;
    }
    for(int i=1;i<=m;i++){
        int l,r,x;
        read(l,r,x);
        qry[x].push_back({l,r,i,0});
    }
    dfs1(rt,0);
    for(int i=1;i<=n;i++){
        if(i!=rt) dg[i]--;
        if(dg[i]>MB){
            solve1(i);
        }
    }
    for(int i=1;i<=n;i++){
        pos[i]=(i+MBL-1)/MBL;
        R[i]=min(n,pos[i]*MBL);
    }
    memset(cnt,0,sizeof(cnt));
    solve2(rt);
    for(int i=1;i<=m;i++){
        put(((ans3[i]*ans3[i]+ans[i])>>1));
    }
    return 0;
}
