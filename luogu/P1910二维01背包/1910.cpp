#include<iostream>
using namespace std;
int n,m,x;
int dp[1010][1010]{},w1[1010],w2[1010],v[1010];
int main(){
	//freopen("ans.in","r",stdin);
	cin>>n>>m>>x;
	for(int i=1;i<=n;i++){
		cin>>v[i]>>w1[i]>>w2[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=w1[i];j--){
			for(int k=x;k>=w2[i];k--){
				dp[j][k]=max(dp[j][k],dp[j-w1[i]][k-w2[i]]+v[i]);
			}
		}
	}
	cout<<dp[m][x];
	return 0;
}
