#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
struct Query{
    int l,r;
}a[MN];
int b[MN],tot,n,m,f[MN][30],mx[MN];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].l>>a[i].r;
        if(a[i].l>a[i].r) a[i].r+=m;
        b[++tot]=a[i].l;
        b[++tot]=a[i].r;
    }
    sort(b+1,b+1+tot);
    tot=unique(b+1,b+1+tot)-b-1;
    for(int i=1;i<=n;i++){
        a[i].l=lower_bound(b+1,b+1+tot,a[i].l)-b;
        a[i].r=lower_bound(b+1,b+1+tot,a[i].r)-b;
    }
    for(int i=1;i<=n;i++){
        mx[a[i].l]=max(mx[a[i].l],a[i].r);
    }
    for(int i=1;i<=tot;i++) mx[i]=max(mx[i],mx[i-1]);
    for(int i=1;i<=tot;i++) f[i][0]=mx[i];
    for(int i=1;i<=20;i++){
        for(int j=1;j<=tot;j++){
            f[j][i]=f[f[j][i-1]][i-1];
        }
    }
    int ans=1e18;
    for(int i=1;i<=n;i++){
        int p=a[i].l,r=b[a[i].l]+m,ret=0;
        for(int j=20;j>=0;j--){
            if(f[p][j]&&b[f[p][j]]<r){
                p=f[p][j];
                ret+=(1<<j);
            }
        }
        if(b[f[p][0]]>=r) ans=min(ans,ret+1);
    }
    if(ans==1e18) cout<<-1;
    else cout<<ans;
    return 0;
}
