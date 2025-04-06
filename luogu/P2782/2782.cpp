#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
int map[1000010];
int main(){
	int n;
	cin>>n;
	int north[n+1],dp[n+1];
	for(int i=1;i<=n;i++){
		int s;
		cin>>north[i]>>s;
		map[north[i]]=s;
		dp[i]=INT_MAX;
	}
	sort(north+1,north+1+n);
	int len=1;
	for(int i=1;i<=n;i++){
		if(map[north[i]]>dp[len]){
			dp[++len]=map[north[i]];
		}else{
			int l=0,r=len;
			while(l<r){
				int mid=(l+r)>>1;
				if(dp[mid]>map[north[i]]) r=mid;
				else l=mid+1;
				dp[l]=min(map[north[i]],dp[l]);
			}
		}
	}
	cout<<len;
	return 0;
}
