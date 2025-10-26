#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=5e3+10,INF=0x3f3f3f3f,mod=1e9+7;
int n,m,c[N];
int f[N][N],g[N][N];
void solve1(){
	g[0][0]=1;
	for(int i=0;i<m;i++){
		for(int j=0;j<=(i>0?c[i]:0);j++){
			for(int k=0;k<=min((i>1?c[i-1]:0),j);k++){
				if(!g[j][k])continue;
				f[c[i+1]-k][j-k]=(f[c[i+1]-k][j-k]+g[j][k])%mod;
			}
		}
		for(int j=c[i+1];j>=0;j--)
			for(int k=0;k<=c[i+1];k++)
				f[j][k]=(f[j][k]+f[j+3][k])%mod;
		for(int j=0;j<=c[i];j++)
			for(int k=0;k<=c[i];k++)
				g[j][k]=0;
		for(int j=0;j<=c[i+1];j++)
			for(int k=0;k<=c[i+1];k++)
				g[j][k]=f[j][k],f[j][k]=0;
	}
	cout<<g[0][0]<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int t;cin>>t;
		c[t]++;
	}
	solve1();
	return 0;
}

