#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
constexpr int K0[10]={0,6,5,1,2,7,8,4,3,9},K1[7]={0,4,1,3,5,2,6};
int n,K;


void solve(){
	int n,k;
	cin>>n>>k;
	if(k==0){
		if(n<8) cout<<-1<<endl;
		else{
			vector<int> tmp = {3,4,8,7,2,1,5,6};
			for(int i=0;i<n-8;i++) cout<<i+1<<' ';
			for(int i=0;i<8;i++) cout<<tmp[i]+n-8<<' ';
			cout<<endl;
		}
	}
	else if(k==1){
		vector<int> tmp = {2,5,3,1,4};
		if(n==1) cout<<1<<endl;
		else if(n<5) cout<<-1<<endl;
		else{
			for(int i=0;i<n-5;i++) cout<<i+1<<' ';
			for(int i=0;i<5;i++) cout<<tmp[i]+n-5<<' ';
			cout<<endl;
		}
	}
	else{
		for(int i=0;i<n-k;i++) cout<<i+1<<' ';
		for(int i=n-k;i<n;i++) cout<<2*n-k-i<<' ';
		cout<<endl;
	}
}



int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}