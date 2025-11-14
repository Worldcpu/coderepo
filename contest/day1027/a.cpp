#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,K,a[MN],sum,pj;
unordered_map<int,int> cnt;

long long checkSM(int k){ // 小的变大
    long long ret=0;
    for(int i=1;i<=n;i++)
        if(a[i]<k) ret+=k-a[i];
    return ret;
}

long long checkbig(int k){ // 大的变小
    long long ret=0;
    for(int i=1;i<=n;i++)
        if(a[i]>k) ret+=a[i]-k;
    return ret;
}

void solve(){
    cin>>n>>K;
    sum=0; cnt.clear();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
        cnt[a[i]]++;
    }
    if(cnt[a[1]]==n){
        cout<<0<<'\n';
        return;
    }
    pj=sum/n;

    int l=pj+1, r=1e15+15, retb=r;
    while(l<=r){
        int mid=(l+r)>>1;
        if(checkbig(mid)<=K) r=mid-1,retb=mid;
        else l=mid+1;
    }

    l=0; r=pj;
    int retm=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(checkSM(mid)<=K) l=mid+1,retm=mid;
        else r=mid-1;
    }
    cout<<retb-retm<<'\n';
}

signed main(){
    int T; cin>>T;
    while(T--) solve();
}
