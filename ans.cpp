#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define fi first
#define se second

const int maxn=1e6+5;

template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

struct Edge
{
    int tot;
    int head[maxn];
    struct edgenode{int to,nxt;}edge[maxn*2];
    inline void add(int x,int y)
    {
        tot++;
        edge[tot].to=y;
        edge[tot].nxt=head[x];
        head[x]=tot;
    }
}T;


int n,n0,m,flg;
int a[maxn],ans[maxn];

namespace fhq_treap
{
    #define lch(p) tr[p].lch
    #define rch(p) tr[p].rch
    int tot;
    struct fhqnode{int pri,val,sz,lch,rch,tag,fa,sum;}tr[maxn];
    inline int newnode(int val){tr[++tot].pri=rand();tr[tot].sz=1;tr[tot].val=val;tr[tot].sum=1;return tot;}
    inline void updata(int p)
    {
        tr[p].sz=tr[lch(p)].sz+tr[rch(p)].sz+tr[p].sum;
        if(lch(p)) tr[lch(p)].fa=p;
        if(rch(p)) tr[rch(p)].fa=p;
        tr[p].fa=0;
    }
    inline void push_down(int p)
    {
        if(!tr[p].tag) return ;
        if(lch(p)) tr[lch(p)].val+=tr[p].tag,tr[lch(p)].tag+=tr[p].tag;
        if(rch(p)) tr[rch(p)].val+=tr[p].tag,tr[rch(p)].tag+=tr[p].tag;
        tr[p].tag=0;
    }
    inline void merge(int &p,int x,int y)
    {
        if(!x||!y) {p=x^y;return ;}
        push_down(x),push_down(y);
        if(tr[x].pri<tr[y].pri) p=y,merge(lch(p),x,lch(y));
        else p=x,merge(rch(p),rch(x),y);
        updata(p);
    }
    inline void spiltval(int p,int &x,int &y,int k)
    {
        if(!p) {x=y=0;return ;}
        push_down(p);
        if(tr[p].val<=k) x=p,spiltval(rch(p),rch(x),y,k),updata(x);
        else y=p,spiltval(lch(p),x,lch(y),k),updata(y);
    }
    inline void spiltsiz(int p,int &x,int &y,int k)
    {
        if(!p) {x=y=0;return ;}
        push_down(p);
        if(tr[lch(p)].sz+tr[p].sum<=k) x=p,spiltsiz(rch(p),rch(x),y,k-(tr[lch(p)].sz+tr[p].sum)),updata(x);
        else y=p,spiltsiz(lch(p),x,lch(y),k),updata(y);
    }
    inline int frrch(int p){while(rch(p)) push_down(p),p=rch(p);return p;}
    inline int frlch(int p){while(lch(p)) push_down(p),p=lch(p);return p;}
}
using namespace fhq_treap;
namespace Tree_Div
{
    int tag;
    set<pii>s;
    int siz[maxn],fa[maxn],tp[maxn],dep[maxn],hso[maxn],rt[maxn],frt[maxn],rttag[maxn],rts[maxn];
    vector<int>lik[maxn];
    inline void dfs_pre(int u,int f)
    {
        dep[u]=dep[f]+1,fa[u]=f;siz[u]=1;
        for(int i=T.head[u];i;i=T.edge[i].nxt)
        {
            int v=T.edge[i].to;dfs_pre(v,u);
            siz[u]+=siz[v];
            if(siz[hso[u]]<siz[v]) hso[u]=v;
        }
    }
    inline void dfs(int u,int top)
    {
        tp[u]=top;lik[top].emplace_back(u);
        if(hso[u]) dfs(hso[u],top);
        for(int i=T.head[u];i;i=T.edge[i].nxt)
        {
            int v=T.edge[i].to;
            if(v==hso[u]) continue;
            dfs(v,v);
        }
    }
}
using namespace Tree_Div;
struct DSU
{
    int f[maxn];
    inline void init(int n){for(int i=1;i<=n;i++) f[i]=i;}
    inline int fr(int x){return f[x]==x?x:f[x]=fr(f[x]);}
    inline void merge(int x,int y){int fx=fr(x),fy=fr(y);if(fx!=fy) f[fy]=fx;}
}F;

//更改时间标记
//rt[x] 是 x 的平衡树的编号
//rttag[x] 存的是上一次更新平衡树 x 的时刻
inline void chgtag(int x)
{
    if(!rt[x]) {rttag[x]=tag;return ;}
    tr[rt[x]].val-=(tag-rttag[x]);tr[rt[x]].tag-=(tag-rttag[x]);
    //向上跳了 tag-rttag[x] 步
    rttag[x]=tag;
}
//更改堆
//rts[x] 记录了 x 平衡树在堆中插入的值
inline void sera(int x)
{
    chgtag(x);
    if(!rt[x]||rts[x]==-1) return ;
    frt[rt[x]]=0;
    s.erase({rts[x],x});
    rts[x]=-1;frt[rt[x]]=x;
}
inline void sins(int x)
{
    chgtag(x);
    if(!rt[x]) return ;
    frt[rt[x]]=0;
    int tmp=frlch(rt[x]);//找到平衡树中最左的节点
    s.insert({tr[tmp].val+tag+flg,x});//flg 是一个操作参数下文提到
    rts[x]=tr[tmp].val+tag+flg;frt[rt[x]]=x;
}
//向重链对应平衡树中插入数
inline void ins(int x,int res)
{
    chgtag(x);
    int tmp=0;frt[rt[x]]=0;
    sera(x);
    spiltval(rt[x],rt[x],tmp,tr[res].val);
    int tmp1=frrch(rt[x]);
    if(tr[tmp1].val==tr[res].val)
    {
        spiltsiz(rt[x],rt[x],tmp1,tr[rt[x]].sz-tr[tmp1].sum);
        tr[tmp1].sum+=tr[res].sum,tr[tmp1].sz+=tr[res].sum,F.merge(tmp1,res);
        //F.merge 是并查集中的操作
        merge(rt[x],rt[x],tmp1);
    }
    else merge(rt[x],rt[x],res);
    merge(rt[x],rt[x],tmp);//插入 res
    sins(x);
    frt[rt[x]]=x;
}
//重链对应平衡树中删除数
//flg=1 表示删除一个标记，flg=0 表示整个点从树上删除
inline int era(int x,int sum,int flg)//删除位于 sum+1 位置的点
{
    chgtag(x);
    frt[rt[x]]=0;
    int tmp=0,tmp1=0;
    sera(x);
    spiltsiz(rt[x],rt[x],tmp,sum);
    spiltsiz(tmp,tmp,tmp1,tr[frlch(tmp)].sum);
    if(flg)
    {
        tr[tmp].sum--;
        if(tr[tmp].sum) merge(tmp1,tmp,tmp1);
    }
    merge(rt[x],rt[x],tmp1);
    sins(x);
    frt[rt[x]]=x;
    return tmp;//返回删除点的编号（后面加入另外一棵平衡树可能要用）
}
//插入删除标记
inline int add(int x)
{
    int res=newnode(dep[x]-dep[tp[x]]);
    ins(tp[x],res);
    return res;
}
inline int del(int x)
{
    stack<int>stk;
    int p=x,sum=tr[lch(x)].sz,tmp=0;
    while(p) stk.push(p),p=tr[p].fa;
    p=stk.top();tmp=frt[p];
    while(p!=x)
    {
        if(rch(p)==stk.top()) sum+=tr[lch(p)].sz+tr[p].sum;
        p=stk.top();stk.pop();
    }
    //定位 x 是平衡树上 sum+1 位置的点
    //tmp 求出 x 对应原树上的点
    era(tmp,sum,1);
    return lik[tmp][tr[x].val];
}
//向 u 集中
inline void work(int u)
{
    int x=u,lst=0;flg=1;//由于时刻 tag 目前不需要更新，需要使用 flg 修正加入堆的点的时刻
    //lst 是上次的重链顶
    while(x)
    {
        int tx=tp[x],val=dep[x]-dep[tx]-(u==x),tmp=0,tmp1=0;
        sera(tx);
        frt[rt[tx]]=0;
        chgtag(tx);
        spiltval(rt[tx],rt[tx],tmp,val);
        //取出距离连顶小于等于 val 的点
        if(rt[tx]) tr[rt[tx]].val++,tr[rt[tx]].tag++;//整体下移
        if(u==x) spiltval(tmp,tmp1,tmp,val+1);//特判 u 位置的点
        if(tmp) tr[tmp].val--,tr[tmp].tag--;//整体上移
        if(u==x) merge(tmp,tmp1,tmp);
        tmp1=frrch(rt[tx]);
        //这里使用 while 是因为平衡树合并了大部分权值相同的点，但无法避免一些点没有被合并，如 merge 操作
        while(tr[tmp1].val>val&&u!=x)//判断是否要下移
        {
            era(tx,tr[rt[tx]].sz-tr[tmp1].sum,0);
            tr[tmp1].val=tr[tmp1].tag=0;tr[tmp1].sz=tr[tmp1].sum;
            ins(lst,tmp1);
            tmp1=frrch(rt[tx]);
        }
        merge(rt[tx],rt[tx],tmp);
        sins(tx);
        frt[rt[tx]]=tx;lst=tx;x=fa[tx];
    }
    flg=0;x=u;
    while(x) rttag[tp[x]]=tag+1,x=fa[tp[x]];//重链上的点整体更新时刻标记
    tag++;
    while(!s.empty())//堆向上跳
    {
        auto it=s.begin();if(it->fi>=tag) break;
        int res=it->se,tmp=era(res,0,0);
        tr[tmp].val=dep[fa[res]]-dep[tp[fa[res]]];tr[tmp].tag=0;tr[tmp].sz=tr[tmp].sum;
        ins(tp[fa[res]],tmp);
    }
}

vector<pii>vec[2][maxn];

int main()
{
    tr[0].val=-1;
    read(n),read(n0),read(m);
    for(int i=2;i<=n;i++) read(fa[i]),T.add(fa[i],i);
    for(int i=1;i<=n0;i++) read(a[i]);
    for(int i=1;i<=m;i++)
    {
        int l,r,x;
        read(l),read(r),read(x);
        vec[0][l].push_back({x,i});
        vec[1][r].push_back({x,i});
    }
    dfs_pre(1,0);dfs(1,1);
    F.init(m);
    for(int i=1;i<=n0;i++)
    {
        for(auto v:vec[0][i]) ans[v.se]=add(v.fi);
        work(a[i]);
        for(auto v:vec[1][i]) ans[v.se]=del(F.fr(ans[v.se]));
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
}
