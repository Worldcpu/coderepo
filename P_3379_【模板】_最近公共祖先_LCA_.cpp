#include<bits/stdc++.h>
using namespace std;
#define TIME static_cast<double>(clock()-start)/CLOCKS_PER_SEC
int n,m,s;
struct Node{
	int dep,fth;
	vector<int> son;
}a[500010];
struct Edge{
	vector<int> k;
}e[500010];
bool fk[500010];
int f[500010][21],lg=0;

int find(int x,int y)
{
	if(x==y)
		return x;
	for(int i=lg;i>=0;i--)
	{
		if(f[x][i]!=f[y][i])
			return find(f[x][i],f[y][i]);
	}
}

void work(int x,int father)
{
	if(x==s)
	{
		for(int i=0;i<a[x].son.size();i++)
			work(a[x].son[i],x);
	}
	else
	{
		f[x][0]=father;
		for(int i=1;i<=log2(a[x].dep);i++)
			f[x][i]=f[f[x][i-1]][i-1];
//		cout<<x<<":"<<endl;
//		for(int i=0;i<=log2(a[x].dep);i++)
//			cout<<i<<" "<<f[x][i]<<endl;
		for(int i=0;i<a[x].son.size();i++)
			work(a[x].son[i],x);
	}
}

int balance_deep(int u,int v,int i)
{
//	cout<<u<<' '<<v<<' '<<i<<' '<<f[v][i]<<endl;
	if(a[f[v][i]].dep==a[u].dep)
		return f[v][i];
	if(a[f[v][i]].dep<a[u].dep)
		return balance_deep(u,v,i-1);
	if(a[f[v][i]].dep>a[u].dep)
		return balance_deep(u,f[v][i],i);
}

void dfs(int father,int now,int deep)//make tree
{
	fk[now]=false;
	a[now].fth=father;
	a[now].dep=deep;lg=max(lg,deep);
	for(int i=0;i<e[now].k.size();i++)
		if(fk[e[now].k[i]])
		{
//			cout<<now<<"->"<<e[now].k[i]<<endl;
			a[now].son.push_back(e[now].k[i]);
			dfs(now,e[now].k[i],deep+1);
		}
}

int main()
{
	clock_t start=clock();
	memset(fk,true,sizeof(fk));
	memset(f,0,sizeof(f));
	a[0].dep=-1;
	cin>>n>>m>>s;
	int u,v;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		e[u].k.push_back(v);
		e[v].k.push_back(u);
	}
	dfs(0,s,0);
	lg=log2(lg)+1;
	work(s,0);
	while(m--)
	{
		cin>>u>>v;
		int du=a[u].dep;
		int dv=a[v].dep;
		if(du>dv)
		{
			swap(u,v);
			swap(du,dv); 
		}
		if(du!=dv)
			v=balance_deep(u,v,lg);
		//cout<<u<<' '<<v<<endl;
		if(u==v)
			cout<<u<<endl;
		else
		{
			int ans=find(u,v);
			cout<<ans<<endl;
		}
	}
	return 0;
}
