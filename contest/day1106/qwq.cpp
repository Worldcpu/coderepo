#include <bits/stdc++.h>
using namespace std;

#define int long long

int read(){
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){ch=getchar();if(ch=='-')f=-1;}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int N=1e7+5;
int n,m,k,vis[N],dis[N],ans,c[N],fa[N];
vector<int> v[N];
struct edge{
	int u,v,w;
	bool operator<(const edge &o)const{
		return w<o.w;
	}
}g[N];

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

int kruskal(){
	sort(g+1,g+m+1);
	int ans=0;
	for(int i=1;i<=m;i++){
		int u=find(g[i].u),v=find(g[i].v),w=g[i].w;
		if(u==v)continue;
		fa[v]=u;
		ans+=w;
	}
	return ans;
}

signed main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1,u,v,w;i<=m;i++){
		u=read(),v=read(),w=read();
		g[i]={u,v,w};
	}
	iota(fa+1,fa+n+k+1,1);
	int ans=0;
	for(int i=1;i<=k;i++){
		c[i]=read();
		for(int j=1;j<=n;j++){
			int tmp;
			tmp=read();
			if(tmp==0)fa[find(n+i)]=find(j);
			else g[++m]={n+i,j,tmp};
		}
	}
	cout<<kruskal();
	return 0;
}
