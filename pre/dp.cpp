#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
typedef unsigned long long ull;
#define N 100005
#define For(i,x,y)for(i=x;i<=(y);i++)
bool bo[N];
queue<int>p,q;
ull R=GetTickCount();
int deg[N][2],dep[N],fa[N];
inline int Rand(int _,int __)
{
	R^=R<<13;
	R^=R>>7;
	R^=R<<17;
	return R%(__-_+1)+_;
}
int find(int p)
{
	if(p!=fa[p])fa[p]=find(fa[p]);
	return fa[p];
}
inline void unite(int p,int q)
{
	p=find(p),q=find(q);
	if(p==q)return;
	if(dep[p]<dep[q])fa[p]=q;
	else fa[q]=p;
	if(dep[p]==dep[q])dep[p]++;
}
int main()
{
	freopen("P7771.in","w",stdout);
	int n=Rand(1,100000),m=Rand(190000,200000),i,u,v;
	cout<<n<<' '<<m;
	For(i,1,n)fa[i]=i;
	For(i,1,m>>1)
	{
		u=Rand(1,n),v=Rand(1,n);
		cout<<endl<<u<<' '<<v;
		unite(u,v);
		deg[u][0]++;
		deg[v][1]++;
	}
	m-=m>>1;
	For(i,1,n)
	if(deg[i][0]<deg[i][1])p.push(i);
	else if(deg[i][0]>deg[i][1])q.push(i);
	while(m)
	{
		if(p.empty()||q.empty())break;
		u=p.front();
		v=q.front();
		p.pop();
		q.pop();
		unite(u,v);
		cout<<endl<<u<<' '<<v;
		deg[u][0]++;
		deg[v][1]++;
		if(deg[u][0]<deg[u][1])p.push(u);
		if(deg[v][0]>deg[v][1])q.push(v);
		m--;
	}
	For(i,1,n-1)
	if(find(i)!=find(n))
	{
		cout<<endl<<n<<' '<<i<<endl<<i<<' '<<n;
		m-=2;
		unite(n,i);
	}
	if(m<2)
	while(1);
	while(m>Rand(0,1))
	{
		u=Rand(1,n);
		cout<<endl<<u<<' '<<u;
		m--;
	}
	if(m)cout<<endl<<Rand(1,n)<<' '<<Rand(1,n);
	return 0;
}