#include<bits/stdc++.h>
#define N 200005
#define M 30
#pragma GCC optimize("O3")
using namespace std;
int n,m,ans,a[N];
struct Trie
{
	int t[N*M][2],pos[N*M],cnt;
	void clear()
	{
		for(int i=1;i<=cnt;i++) t[i][0]=t[i][1]=pos[i]=0;
		cnt=1;
		return;
	}
	void insert(int x,int y)//插入一个数，数值为 x，下标为 y
	{
		int rt=1;
		for(int i=M;i>=0;i--)
		{
			bool now=(x&(1<<i));
			if(!t[rt][now]) t[rt][now]=++cnt;
			rt=t[rt][now];
			pos[rt]=max(pos[rt],y);//子树内下标最大值
		}
		return;
	}
	int query(int x)//返回满足 a[l]^a[r]>=k 的最大的 l
	{
		int rt=1,res=0,maxx=-1;
		for(int i=M;i>=0;i--)
		{
			bool now=(x&(1<<i));
			if(t[rt][now^1])//可以走相反的一位
			{
				if((res+(1<<i))>=m) maxx=max(maxx,pos[t[rt][now^1]]),rt=t[rt][now];//能找到答案，走相同的一位
				else rt=t[rt][now^1],res+=(1<<i);//不能达到要求，走相同的一位
			}
			else if(t[rt][now]) rt=t[rt][now];//走不了相反的
			else break;//叶子结点
		}
		return maxx;
	}
}t;
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(m==0) {cout<<1<<"\n";return;}//特判
	ans=1e9;
	t.clear();
	for(int i=1;i<=n;i++)
	{
		t.insert(a[i],i);
		int res=t.query(a[i]);
		if(res!=-1) ans=min(ans,i-res+1);
	}
	if(ans==1e9) cout<<-1<<"\n";
	else cout<<ans<<"\n";
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
