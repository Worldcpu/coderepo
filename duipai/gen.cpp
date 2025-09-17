#include<bits/stdc++.h>
using namespace std;
random_device seed;
mt19937 mt(seed());
const int N = 1000000,V = 100000;
int a[N];
int main(){
    freopen("dp.in","w",stdout);
	int n = 200,m = 1000;
	cout<<n<<' '<<m<<'\n';
	for(int i = 1;i<=n;i++){
		cout<<(a[i] = mt()%V)<<' ';
	}
	cout<<'\n';
	for(int i = 1;i<=m;i++){
		int op = mt()%2 + 1,l = mt()%n + 1,r = mt()%n + 1;
		if(l > r){
			swap(l,r);
		}
		if(op == 1){
			int v = mt()%V;
			for(int i = l;i<=r;i++){
				if(a[i] > v){
					a[i]-=v;
				}
			}
			cout<<op<<' '<<l<<' '<<r<<' '<<v<<'\n';
		}else{
			cout<<op<<' '<<l<<' '<<r<<' '<<(a[mt()%(r - l + 1) + l])%V<<'\n';
		}
	}
}
