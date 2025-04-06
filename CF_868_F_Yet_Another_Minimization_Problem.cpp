#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=1e5+15;
int n,mk,a[MN],cnt[MN],wl=1,wr;
ll f[MN][2],now,pre=1,w;

inline ll cost(int l, int r) {
    while (wl > l) wl--, w += cnt[a[wl]]++;
    while (wr < r) wr++, w += cnt[a[wr]]++;
    while (wl < l) w -= --cnt[a[wl]], wl++;
    while (wr > r) w -= --cnt[a[wr]], wr--;
    return w;
}
inline ll clac(int i, int j) {
    return f[j][pre] + cost(j+1, i);
}

void dfs(int l,int r,int kl,int kr){
    int mid=(l+r)>>1,k=kl;
    ll kv=clac(mid,k);
    for(int i=kl;i<=min(kr,mid);i++){
        ll tmp=clac(mid,i);
        if(tmp<kv){
            k=i;
            kv=tmp;
        }
    }
    f[mid][now]=kv;
    if(mid>l) dfs(l,mid-1,kl,k);
    if(mid<r) dfs(mid+1,r,k,kr);
}

int main(){
    cin>>n>>mk;
    wr=n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[i][now]=(w+=cnt[a[i]]++);
    }
    for(int i=2;i<=mk;i++){
        swap(now,pre);
        dfs(1,n,1,n);
    }
    cout<<f[n][now];
    return 0;
}