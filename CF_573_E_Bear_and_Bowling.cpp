#include<bits/stdc++.h>
#define int long long
#define maxn 100005
using namespace std;
int n,m,a[maxn];
int f[maxn];
signed main()
{
	cin>>n;
	memset(f,-0x3f,sizeof(f));
    f[0]=0;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j>0;j--)
		{
			f[j]=max(f[j],f[j-1]+j*a[i]);
		}
	}
    int maxx=0;
	for(int i=1;i<=n;i++){
        maxx=max(maxx,f[i]);
    }
    cout<<maxx;
}