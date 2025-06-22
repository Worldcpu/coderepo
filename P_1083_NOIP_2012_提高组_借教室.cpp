#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int cf[MN],rst[MN],a[MN],n,m,L[MN],R[MN],d[MN];

bool check(int mid){
    memset(cf,0,sizeof(cf));
    for(int i=1;i<=mid;i++){
        cf[L[i]]+=d[i];
        cf[R[i]+1]-=d[i];
    }
    for(int i=1;i<=n;i++) {
        a[i]=a[i-1]+cf[i];
        if(a[i]>rst[i]) return 0;
    }
    return 1;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>rst[i];
    }
    for(int i=1;i<=m;i++) cin>>d[i]>>L[i]>>R[i];
    if(check(m)){
        cout<<0;
        return 0;
    }
    int l=1,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1;
        else r=mid;
    }
    cout<<"-1"<<'\n'<<l;
    return 0;
}
