#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=114514;
constexpr double eps=1e-6,INF=1e18;
int n,W,w[MN],t[MN];
int f[MN],v[MN];

int check(int mid){
    for(int i=1;i<=W;i++){
        f[i]=-INF;
    }
    for(int i=1;i<=n;i++){
        for(int j=W;j>=0;j--){
            if(f[j]==(-INF)) continue;
            int k=min(W,j+w[i]);
            f[k]=max(f[k],f[j]+t[i]-mid*w[i]);
        }
    }
    return f[W]>=0;
}

signed main(){
    cin>>n>>W;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>t[i];
        t[i]=t[i]*1000;
    }
    int l=0,r=1e6;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1;
        else r=mid-1;
    }
    cout<<(int)(r);
    return 0;
}
