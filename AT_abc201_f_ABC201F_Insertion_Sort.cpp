#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f3f3f3f3f;
int n,p[MN],a[MN],b[MN],c[MN],sa[MN],sb[MN],sc[MN],f[MN];

struct BIT{
    int t[MN];

    BIT(){
        memset(t,0x3f,sizeof(t));
    }

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]=min(t[x],k);
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=INF;
        while(x){
            ret=min(ret,t[x]);
            x-=lowbit(x);
        }
        return ret;
    }

}bit;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        p[x]=i;
    }
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];
    for(int i=1;i<=n;i++){
        sa[i]=sa[i-1]+a[i];
        sb[i]=sb[i-1]+min(a[i],b[i]);
        sc[i]=sc[i-1]+min(a[i],c[i]);
    }
    int ans=INF;
    for(int i=1;i<=n;i++){
        f[i]=min(sb[i-1],bit.query(p[i])+sa[i-1]);
        ans=min(ans,f[i]+sc[n]-sc[i]);
        bit.modify(p[i],f[i]-sa[i]);
    }
    cout<<ans;
    

    return 0;
}
