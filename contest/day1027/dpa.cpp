#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int n,K;
multiset<int> st;

void init(){
	st.clear();
}

void solve(){
	cin>>n>>K;
	init();
	if(n==1){
		cout<<0<<'\n';
		return;
	}
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		st.insert(x);
	}
	while(K--){
		int mx=*((--st.end()));
		mx--;
		st.insert(mx);
        st.erase((--st.end()));
		int mn=*(st.begin());
		st.erase(st.begin());
		mn++;
		st.insert(mn);
	}
	cout<<(*(--st.end()))-(*st.begin())<<'\n';
}

int main(){
	// freopen("a.in","r",stdin);
	// freopen("a.out","w",stdout);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}