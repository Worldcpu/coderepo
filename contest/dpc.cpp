#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge { int to; int id; ll w; };
struct EInfo { int u,v; ll w; };

int N, M;
vector<vector<Edge>> g;
vector<EInfo> edges;

const int LOGN = 20;
vector<int> parent0;
vector<int> depth0;
vector<array<int,LOGN>> up;
vector<ll> dist0;
vector<int> sz, heavy, head, in, outv, rin;
int timer_glob = 0;

void dfs1(int u, int p){
	parent0[u] = p;
	up[u].fill(0);
	up[u][0] = (p==0?u:p);
	for(int k=1;k<LOGN;k++) up[u][k] = up[ up[u][k-1] ][k-1];
	sz[u]=1; heavy[u]=0;
	for(auto &e: g[u]){
		int v=e.to;
		if(v==p) continue;
		depth0[v]=depth0[u]+1;
		dist0[v]=dist0[u]+e.w;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[v] > (heavy[u]?sz[heavy[u]]:0)) heavy[u]=v;
	}
}

void dfs2(int u, int h){
	head[u]=h;
	in[u]=++timer_glob;
	rin[in[u]] = u;
	if(heavy[u]) dfs2(heavy[u], h);
	for(auto &e: g[u]){
		int v=e.to;
		if(v==parent0[u] || v==heavy[u]) continue;
		dfs2(v, v);
	}
	outv[u]=timer_glob;
}

int lca(int a,int b){
	if(a==b) return a;
	if(depth0[a]<depth0[b]) swap(a,b);
	int diff = depth0[a]-depth0[b];
	for(int k=0;k<LOGN;k++) if(diff&(1<<k)) a = up[a][k];
	if(a==b) return a;
	for(int k=LOGN-1;k>=0;k--) if(up[a][k]!=up[b][k]) { a=up[a][k]; b=up[b][k]; }
	return parent0[a];
}

struct SegNode {
	int u, v;     
	ll du, dv;     
	ll len;     
	ll lz;     
	SegNode(): u(0), v(0), du(0), dv(0), len(0), lz(0) {}
};

struct SegTree {
	int n;
	vector<SegNode> st;
	SegTree(int _n=0){ init(_n); }
	void init(int _n){
		n=_n;
		st.assign(4*n+5, SegNode());
	}
	function<ll(int)> point_q; 
	inline ll dist_nodes(int a, ll da, int b, ll db){
		ll la = (da>=0?da:point_q(in[a]));
		ll lb = (db>=0?db:point_q(in[b]));
		int w = lca(a,b);
		ll lw = point_q(in[w]);
		return la + lb - 2*lw;
	}
	
	SegNode merge_node(const SegNode &L, const SegNode &R){
		if(L.u==0) return R;
		if(R.u==0) return L;
		SegNode res;
		res.lz = 0;
		res.len = L.len;
		res.u = L.u; res.v = L.v;
		if(R.len > res.len){ res.len = R.len; res.u = R.u; res.v = R.v; }
		int ls[2] = {L.u, L.v};
		int rs[2] = {R.u, R.v};
		ll ldu[2] = {L.du, L.dv};
		ll rdu[2] = {R.du, R.dv};
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				if(ls[i]==0 || rs[j]==0) continue;
				ll d_lca = point_q(in[lca(ls[i], rs[j])]);
				ll cand = ldu[i] + rdu[j] - 2*d_lca;
				if(cand > res.len){
					res.len = cand;
					res.u = ls[i];
					res.v = rs[j];
				}
			}
		}
		res.du = point_q(in[res.u]);
		res.dv = point_q(in[res.v]);
		return res;
	}
	
	void build(int p, int l, int r){
		st[p].lz = 0;
		if(l==r){
			int node = rin[l];
			st[p].u = node; st[p].v = node;
			st[p].du = st[p].dv = dist0[node];
			st[p].len = 0;
			return;
		}
		int m=(l+r)/2;
		build(p<<1,l,m);
		build(p<<1|1,m+1,r);
		st[p] = merge_node(st[p<<1], st[p<<1|1]);
	}
	void push(int p){
		ll z = st[p].lz;
		if(z==0) return;
		for(int id : {p<<1, p<<1|1}){
			st[id].lz += z;
			st[id].du += z;
			st[id].dv += z;
		}
		st[p].lz = 0;
	}
	void add_range(int p, int l, int r, int ql, int qr, ll v){
		if(ql>r || qr<l) return;
		if(ql<=l && r<=qr){
			st[p].lz += v;
			st[p].du += v;
			st[p].dv += v;
			return;
		}
		push(p);
		int m=(l+r)/2;
		add_range(p<<1,l,m,ql,qr,v);
		add_range(p<<1|1,m+1,r,ql,qr,v);
		st[p] = merge_node(st[p<<1], st[p<<1|1]);
	}
	ll point_query(int p, int l, int r, int pos){
		if(l==r) return st[p].du;
		push(p);
		int m=(l+r)/2;
		if(pos<=m) return point_query(p<<1,l,m,pos);
		else return point_query(p<<1|1,m+1,r,pos);
	}
	SegNode query_range(int p, int l, int r, int ql, int qr){
		if(ql>r || qr<l) return SegNode();
		if(ql<=l && r<=qr) return st[p];
		push(p);
		int m=(l+r)/2;
		SegNode L = query_range(p<<1,l,m,ql,qr);
		SegNode R = query_range(p<<1|1,m+1,r,ql,qr);
		return merge_node(L,R);
	}
};


int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>N>>M;
	g.assign(N+1, {});
	edges.assign(N, EInfo());
	for(int i=1;i<=N-1;i++){
		int u,v; ll w; cin>>u>>v>>w;
		edges[i].u=u; edges[i].v=v; edges[i].w=w;
		g[u].push_back({v,i,w});
		g[v].push_back({u,i,w});
	}
	parent0.assign(N+1,0);
	depth0.assign(N+1,0);
	up.assign(N+1, array<int,LOGN>());
	dist0.assign(N+1,0);
	sz.assign(N+1,0);
	heavy.assign(N+1,0);
	head.assign(N+1,0);
	in.assign(N+1,0);
	outv.assign(N+1,0);
	rin.assign(N+1,0);
	
	depth0[1]=0; dist0[1]=0;
	dfs1(1,0);
	timer_glob=0;
	dfs2(1,1);
	
	vector<int> edge_child(N,0);
	for(int i=1;i<=N-1;i++){
		int u=edges[i].u, v=edges[i].v;
		if(parent0[u]==v) edge_child[i]=u;
		else if(parent0[v]==u) edge_child[i]=v;
		else {
			if(depth0[u]>depth0[v]) edge_child[i]=u; else edge_child[i]=v;
		}
	}
	
	SegTree st(N);
	st.point_q = [&](int pos)->ll{ return st.point_query(1,1,N,pos); };
	st.build(1,1,N);
	
	while(M--){
		int t; cin>>t;
		if(t==1){
			int i; ll k; cin>>i>>k;
			ll delta = k - edges[i].w;
			edges[i].w = k;
			int ch = edge_child[i];
			if(delta!=0){
				st.add_range(1,1,N,in[ch],outv[ch], delta);
			}
		} else if(t==2){
			int x,y; cin>>x>>y;
			SegNode A = st.query_range(1,1,N,in[x],outv[x]);
			SegNode B = st.query_range(1,1,N,in[y],outv[y]);
			ll ans = 0;
			int as[2] = {A.u, A.v};
			ll ad[2] = {A.du, A.dv};
			int bs[2] = {B.u, B.v};
			ll bd[2] = {B.du, B.dv};
			for(int i=0;i<2;i++) if(as[i]){
				for(int j=0;j<2;j++) if(bs[j]){
					ll d_lca = st.point_q(in[lca(as[i], bs[j])]);
					ll cand = ad[i] + bd[j] - 2*d_lca;
					ans = max(ans, cand);
				}
			}
			cout<<ans<<"\n";
		} else if(t==3){
			int x,a,b; cin>>x>>a>>b;
			SegNode A = st.query_range(1,1,N,in[x],outv[x]);
			SegNode P;
			while(head[a] != head[b]){
				if(depth0[ head[a] ] < depth0[ head[b] ]) swap(a,b);
				SegNode cur = st.query_range(1,1,N,in[ head[a] ], in[a]);
				P = st.merge_node(cur, P);
				a = parent0[ head[a] ];
			}
			if(depth0[a] > depth0[b]) swap(a,b);
			SegNode cur2 = st.query_range(1,1,N,in[a], in[b]);
			P = st.merge_node(P, cur2);
			
			ll ans = 0;
			int as2[2] = {A.u, A.v};
			ll ad2[2] = {A.du, A.dv};
			int ps[2] = {P.u, P.v};
			ll pd[2] = {P.du, P.dv};
			for(int i=0;i<2;i++) if(as2[i]){
				for(int j=0;j<2;j++) if(ps[j]){
					ll d_lca = st.point_q(in[lca(as2[i], ps[j])]);
					ll cand = ad2[i] + pd[j] - 2*d_lca;
					ans = max(ans, cand);
				}
			}
			cout<<ans<<"\n";
		}
	}
	return 0;
}

