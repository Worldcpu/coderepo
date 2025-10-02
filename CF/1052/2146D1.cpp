#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int l,r,p[MN][MN],ans;
set<int> st;

void init(){
    ans=0;
    st.clear();
    for(int i=0;i<=r;i++){
        st.insert(i);
    }
}

void solve(){
    cin>>l>>r;
    init();
    int pos=1;
    while(pos<r) pos=pos<<1|1;
    for(int i=r;i>=l-1;i--){
        while(!st.count(pos-i)) pos>>=1;
        st.erase(pos-i);
    }
    swap(p[1],p[2]);
    cout<<ans<<'\n';
    int qwq=0;
    for(int i=0;i<=r;i++){
        cout<<p[i]<<' ';
    }
    cout<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}