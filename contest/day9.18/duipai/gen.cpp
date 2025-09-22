#include<bits/stdc++.h>
using namespace std;
random_device seed;
mt19937 mt(seed());
const int n=520,r=520,c=520;

int getrd(int l,int r){
	return mt()%(r-l+1)+l;
}

int main(){
	cout<<n<<' '<<r<<' '<<c<<'\n';
	for(int i=1;i<=n;i++){
		cout<<getrd(1,r)<<' '<<getrd(1,c)<<' '<<getrd(1,n)<<'\n';
	}
}
