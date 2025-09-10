#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,m,a[MN],p[MN],ans,f[MN],mxp=1;

bool check(int k){
    f[1]=0;
    for(int i=2;i<=n;i++){
        f[i]=f[i-1];
        if(f[i-1]>=p[i]-1) f[i]=max(f[i],p[i]+k);
        if(f[i-1]>=p[i]-k-1) f[i]=max(f[i],p[i]);
        if(i>2&&f[i-2]>=p[i]-k-1) f[i]=max(f[i],p[i-1]+k);
    }
    if(f[n]>=m-k-1) return 1;
    f[2]=max(p[2],k);
    for(int i=3;i<=n;i++){
        f[i]=f[i-1];
        if(f[i-1]>=p[i]-1) f[i]=max(f[i],p[i]+k);
        if(f[i-1]>=p[i]-k-1) f[i]=max(f[i],p[i]);
        if(i>2&&f[i-2]>=p[i]-k-1) f[i]=max(f[i],p[i-1]+k);
    }
    if(f[n]>=min(m-1,m+p[2]-k-1)) return 1;
    return 0;
}

int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i+n]=a[i]+m;
    }
    sort(a+1,a+1+(n<<1));
    mxp=1;
    for(int i=2;i<=n;i++){
        if(a[mxp+1]-a[mxp]<a[i+1]-a[i]) mxp=i;
    }
    for(int i=1;i<=n;i++){
        p[i]=a[i+mxp];
    }
    int tmp=p[1];
    for(int i=1;i<=n;i++){
        p[i]-=tmp;
    }
    int l=0,r=a[mxp+1]-a[mxp]-1;
    cerr<<l<<' '<<r;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }else l=mid+1;
    }
    cout<<ans;
    return 0;
}