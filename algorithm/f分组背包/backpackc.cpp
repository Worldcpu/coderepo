#include<iostream>
#include<queue>
using namespace std;
const int MN=1010;
struct pack{
	int num,packs=1;
}p[MN];
queue<int> pn;
bool vis[MN]{};
int n,m,v[MN][MN],w[MN][MN],dp[MN+10]{};
int main(){
//	freopen("ans.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int wei,val,c;
		cin>>wei>>val>>c;
		if(vis[c]==0){
			pn.push(c);
			vis[c]=1;
		}else p[c].packs++;
		w[c][p[c].packs]=wei;
		v[c][p[c].packs]=val;
	}
	while(!pn.empty()){
		int f=pn.front();
		pn.pop();
		for(int j=m;j>=0;j--){
			for(int k=1;k<=p[f].packs;k++){
				dp[j]=max(dp[j],dp[j-w[f][k]]+v[f][k]);
			}
		}
	}
	cout<<dp[m];
	return 0;
}
