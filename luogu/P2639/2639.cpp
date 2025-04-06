#include<iostream>
using namespace std;
int main(){
	freopen("ans.in","r",stdin);
	int h,n;
	cin>>h>>n;
	int w[n+1];
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	int dp[h+5]{};
	for(int i=1;i<=n;i++){
		for(int j=h;j>=w[i];j--){
			dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
		}
	}
	cout<<dp[h];
	return 0;
}
