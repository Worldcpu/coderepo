#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=7e5+15;
int n,m,tot,mxr,f[MN][30],a[MN];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        a[l]=max(a[l],r);
        mxr=max(mxr,r);
    }
    for(int i=1;i<=mxr;i++) a[i]=max(a[i],a[i-1]);
    for(int i=0;i<=mxr;i++) f[i][0]=a[i];
    for(int i=1;i<=20;i++){
        for(int j=0;j<=mxr;j++) f[j][i]=f[f[j][i-1]][i-1];
    }
    while(m--){
        int x,y;
        cin>>x>>y;
        int ans=0,p=x;
        for(int i=20;i>=0;i--){
            if(f[p][i]<y){
                p=f[p][i];
                ans+=1<<i;
            }
        }
        if(a[p]>=y) cout<<ans+1<<'\n';
        else cout<<-1<<'\n';
    }
    return 0;
}
