#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],ans,mn,mx,b[MN];

void init(){
    ans=0;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    mn=*min_element(a+1,a+1+n);
    mx=*max_element(a+1,a+1+n);
    ans=mx-mn;
    for(int i=n;i<=n;i++){
        if(a[i]==0) continue;
        for(int j=1;j<=n;j++){
            b[j]=a[j]%a[i];
        }
        mn=*min_element(b+1,b+1+n);
        mx=*max_element(b+1,b+1+n);
        ans=max(ans,mx-mn);
        for(int j=1;j<=n;j++){
            b[j]=a[j]%(a[i]+1);
        }
        mn=*min_element(b+1,b+1+n);
        mx=*max_element(b+1,b+1+n);
        ans=max(ans,mx-mn);
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

// p 似乎只能取 i\in [1,n],(a_i,a_i +1)，本质是钦定mx 和 mn。
// 那我不直接取 max 和 max+1 不就完事了吗？你在搞笑吗？