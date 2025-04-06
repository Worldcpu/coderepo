#include<iostream>
using namespace std;
const int MN=1e4+10;
int n,m,w;
int pre[MN],wei[MN],v[MN],dp[MN]{},ans;
void initpre(){
	for(int i=1;i<=n;i++){
		pre[i]=i;
	}
}
int root(int x){
	if(pre[x]==x) return x;
	pre[x]=root(pre[x]);
	return pre[x];
}
void merge(int x,int y){
	int rx=root(x),ry=root(y);
	pre[rx]=ry;
}
int main(){
	cin>>n>>m>>w;
	initpre();
	for(int i=1;i<=n;i++){
		cin>>wei[i]>>v[i];
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		merge(x,y);
	}
	for(int i=1;i<=n;i++){
		if(pre[i]==i) continue;
		wei[root(i)]+=wei[i];
		v[root(i)]+=v[i];
		wei[i]=0;
		v[i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=w;j>=wei[i];j--){
			dp[j]=max(dp[j],dp[j-wei[i]]+v[i]);
		}
	}
	cout<<dp[w];
	return 0;
}
