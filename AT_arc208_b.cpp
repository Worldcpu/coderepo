#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,K,res[MN];

bool check(int mid){
    res[1]=mid;
    int ret=0;
    for(int i=2;i<=n;i++){
        if(ret<K){
            res[i]=res[i-1]*2-1;
            ret+=res[i-1]-1;
        }else if(ret==K) res[i]=res[i-1];
        if(ret>K){
            int tmp=ret-K;
            res[i]-=tmp;
            ret-=tmp;
        }
    }
    return ret==K;
}

void solve(){
    cin>>n>>K;
    int l=2,r=2e9,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    check(ans);
    for(int i=1;i<=n;i++){
        cout<<res[i]<<' ';
    }
    int qwq=0;
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