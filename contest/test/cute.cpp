#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#define MAXN 500005

using namespace std;

int n,m,ch[MAXN][4],trie_cnt=0,fail[MAXN],head[MAXN],edge_cnt=0;

int rt[MAXN],nodecnt=0,dfn[MAXN],dfncnt=0,h[MAXN],cnt=0,vistag[MAXN];

int fa[MAXN],dep[MAXN],siz[MAXN],top[MAXN],son[MAXN],stk[MAXN],tp=0;

int sz[MAXN],sz2[MAXN];

char str[MAXN];

vector <int> v[MAXN],edge[MAXN];

struct E{
	int to,nxt;
}e[MAXN];

struct seg{
	int lc,rc,val;
}tree[MAXN*20];

bool cmp(int x,int y) { return dfn[x]<dfn[y]; }

void Add_Edge(int x,int y){
	e[++edge_cnt].to=y;
	e[edge_cnt].nxt=head[x];
	head[x]=edge_cnt;
}

int modify(int p,int l,int r,int pos){
	int tmp=++nodecnt;
	tree[tmp]=tree[p];
	tree[tmp].val++;
	if(l==r) return tmp;
	int mid=l+r>>1;
	if(pos<=mid) tree[tmp].lc=modify(tree[p].lc,l,mid,pos);
	else tree[tmp].rc=modify(tree[p].rc,mid+1,r,pos);
	return tmp;
}

int query(int rt1,int rt2,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr) return tree[rt2].val-tree[rt1].val;
	int mid=l+r>>1,ret=0;
	if(mid>=ql) ret+=query(tree[rt1].lc,tree[rt2].lc,l,mid,ql,qr);
	if(mid<qr) ret+=query(tree[rt1].rc,tree[rt2].rc,mid+1,r,ql,qr);
	return ret;
}

void insert(char * s,int val){
	int now=0,len=strlen(s);
	for(int i=0;i<len;i++){
		if(!ch[now][s[i]-'a']) ch[now][s[i]-'a']=++trie_cnt;
		now=ch[now][s[i]-'a'];
	}
	v[now].push_back(val);
}

void getfail(){
	queue <int> q;
	for(int i=0;i<4;i++) if(ch[0][i]) q.push(ch[0][i]);
	int fro;
	while(!q.empty()){
		fro=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			if(ch[fro][i]){
				fail[ch[fro][i]]=ch[fail[fro]][i];
				q.push(ch[fro][i]);
			}
			else ch[fro][i]=ch[fail[fro]][i];
		}
	}
	for(int i=1;i<=trie_cnt;i++) edge[fail[i]].push_back(i);
}

void dfs_fail(int x){
	rt[x]=rt[fail[x]]; dfn[x]=++dfncnt;
	for(int i : v[x]) rt[x]=modify(rt[x],1,1000,i);
	for(int i : edge[x]) dfs_fail(i);
}

void dfs1(int x,int f,int d){
	fa[x]=f; dep[x]=d; siz[x]=1;
	for(int i : edge[x]){
		dfs1(i,x,d+1);
		siz[x]+=siz[i];
		if(siz[i]>siz[son[x]]) son[x]=i;
	}
}

void dfs2(int x,int tp){
	top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(int i : edge[x]) if(i^son[x]) dfs2(i,i);
}

int Lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x]>dep[y]?y:x;
}

int dfs(int x,int f,int val){
	int ret=0;
	sz2[x]=sz[x];
	for(int i=head[x];i;i=e[i].nxt){
		ret+=dfs(e[i].to,x,val);
		sz2[x]+=sz2[e[i].to];
	}
	if(x){
		int tmp=(val-1)/sz2[x]+1;
		if(tmp<=1000) ret+=query(rt[f],rt[x],1,1000,tmp,1000);
	}
	return ret;
}

bool check(int x,int k) { return dfs(0,0,x)>=k; }

int main(){
	cin >> n >> m;
	int val,k,l,r,len,mid,ans,vistot=0;
	while(n--){
		cin >> str >> val;
		insert(str,val);
	}
	getfail();
	dfs_fail(0);
	dfs1(0,0,1);
	dfs2(0,0);
	while(m--){
		++vistot;
		cin >> str >> k;
		edge_cnt=0;
		cnt=0;
		len=strlen(str);
		for(int now=0,i=0;i<len;i++){
			now=ch[now][str[i]-'a'];
			h[++cnt]=now;
			if(vistag[now]==vistot) sz[now]++;
			else sz[now]=1,vistag[now]=vistot;
		}
		sort(h+1,h+cnt+1,cmp);
		stk[tp=1]=0; head[0]=0;
		for(int i=1;i<=cnt;i++){
			if(h[i]==0) continue;
			if(i!=1&&h[i]==h[i-1]) continue;
			l=Lca(stk[tp],h[i]);
			if(l!=stk[tp]){
				while(dfn[l]<dfn[stk[tp-1]]){
					Add_Edge(stk[tp-1],stk[tp]);
					tp--;
				}
				if(dfn[l]>dfn[stk[tp-1]]){
					head[l]=0;
					if(vistag[l]!=vistot) sz[l]=0;
					Add_Edge(l,stk[tp]);
					stk[tp]=l;
				}
				else Add_Edge(l,stk[tp]),tp--;
			}
			head[h[i]]=0; stk[++tp]=h[i];
		}
		for(int i=1;i<tp;i++) Add_Edge(stk[i],stk[i+1]);
		if(!check(1,k)){
			cout << 0 << '\n';
			continue;
		}
		l=1,r=1e9,ans=114514;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid,k)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		cout << ans << '\n';
	}
	return 0;
}
