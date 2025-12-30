#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,ans,a[MN],pre[MN],suf[MN],ptot,stot;
set<int> st;

void init(){
    ans=ptot=stot=0;
    st.clear();
    for(int i=1;i<=n;i++){
        pre[i]=suf[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    for(int i=1;i<=n;i++){
        st.insert(i); 
    }
    for(int i=1;i<=n;i++){
        auto it=st.upper_bound(a[i]);
        if(it==st.begin()) continue;
        pre[++ptot]=i;
        st.erase(prev(it));
    }

    for(int i=1;i<=n;i++){
        st.insert(i);
    }
    for(int i=n;i>=1;i--){
        auto it=st.upper_bound(a[i]);
        if(it==st.begin()) continue;
        suf[++stot]=i;
        st.erase(prev(it));
    }
    for(int i=1;i<=n;i++){
        if(pre[i]>=suf[i]) break;
        ans+=suf[i]-pre[i];
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}