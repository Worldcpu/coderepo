#include<bits/stdc++.h>
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
    mn=*min_element(a+1,a+1+n);
    mx=*max_element(a+1,a+1+n);
    ans=mx-mn;
    for(int i=2,qwq=mx;i<=qwq;i++){
        for(int j=1;j<=n;j++){
            b[j]=a[j]%i;
        }
        mn=*min_element(b+1,b+1+n);
        mx=*max_element(b+1,b+1+n);
        ans=max(ans,mx-mn);
    }
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}