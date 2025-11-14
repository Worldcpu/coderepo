#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,ML=30;
struct Edge{
	int v,id;
};
struct EDge{
	int u,v,w;
}e[MN];
int n,m,edgew[MN],dfn[MN];
vector<Edge> adj[MN];

namespace Distance{ //动态维护 rt->u 的 dis

struct BIT{
	int t[MN];

	private:
		int lowbit(int x){
			return x&-x;
		}

		void modifyval(int x,int k){
			while(x<MN){
				t[x]+=k;
				x+=lowbit(x);
			}
		}

		int querysum(int x){
			int ret=0;
			while(x>0){
				ret+=t[x];
				x-=lowbit(x);
			}
			return ret;
		}
	
	public:
		int query(int x){
			if(x<1||x>n) return 0;
			return querysum(x);
		}

		void modify(int l,int r,int k){
			if(l>r) return;
			modifyval(l,k);
			modifyval(r+1,-k);
		}

		void modify(int pos,int k){
			if(pos<1||pos>n) return;
			modifyval(pos,k);
			modifyval(pos+1,-k);
		}
}bit;

	int Dis(int x){
		return bit.query(dfn[x]);
	}

}using namespace Distance;

namespace Tree{ // Tree 部分
	int dis[MN],st[ML+2][MN],dep[MN],fa[MN],dtot,siz[MN],id[MN];

	void dfs1(int u,int pre){
		dep[u]=dep[pre]+1;
		dfn[u]=++dtot;
		id[dtot]=u;
		siz[u]=1;
		fa[u]=pre;

		for(auto e:adj[u]){
			int v=e.v,w=edgew[e.id];
			if(v==pre) continue;
			dis[v]=dis[u]+w;
			dfs1(v,u);
			siz[u]+=siz[v];
		}
	}

	int cmpdfn(int x,int y){
		return dfn[x]<dfn[y]?x:y;
	}

	void initst(){
		for(int i=1;i<=n;i++){
			st[0][dfn[i]]=fa[i];
		}
		for(int i=1;i<=ML;i++){
			for(int j=1;j+(1<<i)-1<=n;j++){
				st[i][j]=cmpdfn(st[i-1][j],st[i-1][j+(1<<i-1)]);
			}
		}
	}

	int lca(int x,int y){
		if(x==y) return x;
		x=dfn[x],y=dfn[y];
		if(x>y) swap(x,y);
		int lg=__lg(y-x++);
		return cmpdfn(st[lg][x],st[lg][y-(1<<lg)+1]);
	}


	int getdis(int x,int y){
		if(x==0||y==0) return -1;
		return Dis(x)+Dis(y)-2*Dis(lca(x,y));
	}

	bool insub(int x,int y){
		return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1;
	}

}using namespace Tree;

namespace Maxdis{ // 维护最大距离
	struct Node{
		int d[2];

		Node(int xx=0,int yy=0){
			d[0]=xx,d[1]=yy;
		}

		friend bool operator<(const Node &x,const Node &y){
			return getdis(x.d[0],x.d[1])<getdis(y.d[0],y.d[1]);
		}

		friend Node operator+(const Node &x,const Node &y){
			Node ret;
			ret=max(x,y);
			for(int i=0;i<=1;i++){
				for(int j=0;j<=1;j++){
					ret=max(ret,Node(x.d[i],y.d[j]));
				}
			}
			return ret;
		}
	};

	struct Segment{
		#define ls p<<1
		#define rs p<<1|1
		struct SNode{
			int l,r;
			Node val;
		}t[MN<<2];

		void pushup(int p){
			t[p].val=t[ls].val+t[rs].val;
		}

		void build(int p,int l,int r){
			t[p].l=l;
			t[p].r=r;
			if(l==r){
				t[p].val=Node(id[l],id[l]);
				return;
			}
			int mid=(l+r)>>1;
			build(ls,l,mid);
			build(rs,mid+1,r);
			pushup(p);
		}

		void update(int p,int fl,int fr){
			if(t[p].l>=fl&&t[p].r<=fr){
				return;
			}
			int mid=(t[p].l+t[p].r)>>1;
			if(mid>=fl) update(ls,fl,fr);
			if(mid<fr) update(rs,fl,fr);
			pushup(p);
		}

		Node query(int p,int fl,int fr){
			if(t[p].l>=fl&&t[p].r<=fr){
				return t[p].val;
			}
			int mid=(t[p].l+t[p].r)>>1;
			if(mid<fl) return query(rs,fl,fr);
			if(mid>=fr) return query(ls,fl,fr);
			return (query(ls,fl,fr)+query(rs,fl,fr));
		}

		#undef ls
		#undef rs
	}sg;
}using namespace Maxdis;

void solve1(int x,int w){
	auto [u,v,pw]=e[x];
	if(fa[u]==v) swap(u,v);
	bit.modify(dfn[v],dfn[v]+siz[v]-1,w-pw);
	sg.update(1,dfn[v],dfn[v]+siz[v]-1);
	e[x].w=w;
}

void solve2(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	auto rx=sg.query(1,dfn[x],dfn[x]+siz[x]-1);
	auto ry=sg.query(1,dfn[y],dfn[y]+siz[y]-1);

	auto dx0=Dis(rx.d[0]);
	auto dx1=Dis(rx.d[1]);
	auto dy0=Dis(ry.d[0]);
	auto dy1=Dis(ry.d[1]);
	
	if(dx1>dx0){
		swap(rx.d[0],rx.d[1]);
		swap(dx0,dx1);
	}
	if(dy1>dy0){
		swap(ry.d[0],ry.d[1]);
		swap(dy0,dy1);
	}

	if(insub(x,y)){
		cout<<max({getdis(rx.d[0],ry.d[0]),getdis(rx.d[1],ry.d[0])})<<'\n';
	}else{
		cout<<dx0+dy0-2*Dis(lca(x,y))<<'\n';
	}

}

void solve3(int x,int a,int b){
	auto rx=sg.query(1,dfn[x],dfn[x]+siz[x]-1);
	cout<<max({getdis(a,rx.d[0]),getdis(a,rx.d[1]),getdis(b,rx.d[0]),getdis(b,rx.d[1])})<<'\n';
}

signed main(){
	// freopen("c.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[i]={u,v,w};
		edgew[i]=w;
		adj[u].push_back({v,i});
		adj[v].push_back({u,i});
	}

	dfs1(1,0);
	initst();
	for(int i=1;i<=n;i++){
		bit.modify(dfn[i],dis[i]);
	}
	sg.build(1,1,n);



	while(m--){
		int op,x,y,z;
		cin>>op;
		if(op==1){
			cin>>x>>y;
			solve1(x,y);
		}
		if(op==2){
			cin>>x>>y;
			solve2(x,y);
		}
		if(op==3){
			cin>>x>>y>>z;
			solve3(x,y,z);
		}
	}
	return 0;
}