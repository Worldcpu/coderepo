#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10,INF=0x3f3f3f3f;
int n,m,cnt,cas;char s[N];string t[N];
int ed[N],a[N];vector<int> e[N];
struct ACAM
{
	struct node{int nxt,v[26];node(){memset(v,0,sizeof v);nxt=0;}}t[N];int tot=0;
	inline void clear()
	{
		memset(t,0,sizeof t);tot=0;
	}
	inline void insert(char s[],int n,int id)
	{
		int u=0;
		for(int i=1;i<=n;i++){if(!t[u].v[s[i]-'a']) t[u].v[s[i]-'a']=++tot;u=t[u].v[s[i]-'a'];}
		ed[id]=u;
	}
	inline void build()
	{
		queue<int>q;
		for(int i=0;i<26;i++) if(t[0].v[i]) t[t[0].v[i]].nxt=0,q.push(t[0].v[i]);
		while(!q.empty())
		{
			int u=q.front();q.pop();e[u].emplace_back(t[u].nxt);e[t[u].nxt].emplace_back(u);
			for(int i=0;i<26;i++)
				if(t[u].v[i]) t[t[u].v[i]].nxt=t[t[u].nxt].v[i],q.push(t[u].v[i]);
				else t[u].v[i]=t[t[u].nxt].v[i];
		}
	}
}ac;
struct min_max_SGT//Segment_Tree
{
    #define ls (p<<1)
    #define rs (p<<1|1)
    #define mid ((l+r)>>1)
    vector<int>lz,mx;int L,R;//op=1 means max;op=0 means min
    inline void init(int l,int r){L=l,R=r;mx=lz=vector<int>((r-l+10)<<2);}
    inline void pushup(int p){mx[p]=max(mx[ls],mx[rs]);}
    inline void pushdown(int p)
    {
        mx[ls]=max(mx[ls],lz[p]),mx[rs]=max(mx[rs],lz[p]);
        lz[ls]=max(lz[ls],lz[p]),lz[rs]=max(lz[rs],lz[p]);lz[p]=-INF;
    }
    inline void modify(int p,int l,int r,int s,int e,int v)
    {
    	if(p==1) l=L,r=R;if(s>e||s>r||l>e) return;
        if(l>=s&&r<=e)
        {
            mx[p]=max(mx[p],v),lz[p]=max(lz[p],v);return;
        }pushdown(p);
        if(mid>=s) modify(ls,l,mid,s,e,v);
        if(mid<e) modify(rs,mid+1,r,s,e,v);
        pushup(p);
    }
    inline int query(int p,int l,int r,int s,int e)
    {
    	if(p==1) l=L,r=R;if(s>e||s>r||l>e) return 0;
        if(l>=s&&r<=e) return mx[p];
        int res=-INF;pushdown(p);
        if(mid>=s) res=query(ls,l,mid,s,e);
        if(mid<e) res=max(res,query(rs,mid+1,r,s,e));
        return res;
    }
    #undef ls
    #undef rs
    #undef mid
}sgt;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);
        char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
}
using namespace Fast_IO;
namespace tree_decomposition
{
    int d[N],dfn[N];
	inline void clear(int n)
	{
		cnt=0;for(int i=0;i<=n;i++) e[i].clear();
	}
    inline void dfs1(int u,int ff)
    {
        dfn[u]=++cnt;
        for(auto v:e[u])
        {
            if(v==ff) continue;
            dfs1(v,u);
        }d[u]=cnt;
    }
}
using namespace tree_decomposition;
namespace KMP
{
	inline bool chk(char c) { return !(c>='a'&&c<='z'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=' '&&c!=-1; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace KMP;
inline int query(string s)
{
	int u=0,res=0;
	for(auto v:s)
		if(v-'a'<0) break;
		else res=max(res,sgt.query(1,0,0,dfn[u=ac.t[u].v[v-'a']],dfn[ac.t[u].v[v-'a']]));
	return res;
}
inline void solve()
{
	putchar('C'),putchar('a'),putchar('s'),putchar('e'),putchar(' '),putchar('#'),print(++cas),putchar(':'),putchar(' ');
	clear(max(cnt,ac.tot));ac.clear();n=read();
	for(int i=1;i<=n;i++) m=0,rd(s,m),t[i]=s+1,a[i]=read(),ac.insert(s,m,i);
	ac.build();dfs1(0,0);sgt.init(1,cnt);int ans=0;
	for(int i=1;i<=n;i++)
	{
		int w=a[i]+query(t[i]);
		sgt.modify(1,0,0,dfn[ed[i]],d[ed[i]],w);
		ans=max(ans,w);
	}
	print(ans);puts("");
}
signed main()
{
    int T=read();
    while(T--) solve();
    return 0;
}

