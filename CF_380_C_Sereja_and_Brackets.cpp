#include <cstdio>
#include <iostream>
using namespace std;
const int M = 100005;
int read()
{
	int x=0,f=1;char c;
	while((c=getchar())<'0' || c>'9') {if(c=='-') f=-1;}
	while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
void write(int x)
{
	if(x>=10) write(x/10);
	putchar(x%10+'0');
}
int n,m,k,a[M],p[M];
int l[M][20],r[M][20],ml[M][20],mr[M][20];
string s;
signed main()
{
    cin>>s>>m;
    n=s.length();
    s=" "+s;
	for(int i=1;i<=n;i++)
	{
		a[i+1]=a[i];
		if(s[i]=='(') a[i+1]--;
		else a[i+1]++;
	}
	n++;p[k=1]=1;
	for(int i=2;i<=n;i++)
	{
		while(k && a[p[k]]<=a[i]) k--;
		l[i][0]=k?p[k]:0;
		ml[i][0]=i-p[k]-1;
		p[++k]=i;
	}
	p[k=1]=n;
	for(int i=n-1;i>=1;i--)
	{
		while(k && a[p[k]]<=a[i]) k--;
		r[i][0]=k?p[k]:0;
		mr[i][0]=p[k]-i-1;
		p[++k]=i;
	}
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
		{
			l[i][j]=l[l[i][j-1]][j-1];
			r[i][j]=r[r[i][j-1]][j-1];
			ml[i][j]=max(ml[i][j-1],ml[l[i][j-1]][j-1]);
			mr[i][j]=max(mr[i][j-1],mr[r[i][j-1]][j-1]);
		}
	while(m--)
	{
		int a,b,ans=0;
        cin>>a>>b;
        ++b;
		for(int i=19;i>=0;i--)
		{
			if(r[a][i]>=a && r[a][i]<=b)
				ans=max(ans,mr[a][i]),a=r[a][i];
			if(l[b][i]>=a && l[b][i]<=b)
				ans=max(ans,ml[b][i]),b=l[b][i];
		}
		ans=max(ans,b-a);
		write(ans),puts("");
	}
}
