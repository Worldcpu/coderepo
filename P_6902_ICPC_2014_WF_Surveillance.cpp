#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15;
int n,m,mxr,ans=1e9,f[MN][21];
pir a[MN];

void solve(){
    memset(f,0,sizeof(f));
    ans=1e9;
    mxr=0;
    for(int i=1;i<=m;i++){
        cin>>a[i].first>>a[i].second;
        if(a[i].first>a[i].second) a[i].second+=n;
    }
    sort(a+1,a+1+m);
    for(int i=1,now=1;i<=2*n;i++){
        while(now<=m&&a[now].first<=i){
            mxr=max(mxr,a[now].second+1);
            now++;
        }
        f[i][0]=mxr;
    }
    for(int i=1;i<=20;i++){
        for(int j=1;j<=2*n;j++) f[j][i]=f[f[j][i-1]][i-1];
    }
    for(int i=1;i<=2*n;i++){
        int p=i,ret=0;
        for(int j=20;j>=0;j--){
            if(f[p][j]-i<n){
                p=f[p][j];
                ret+=1<<j;
            }
        }
        p=f[p][0];
        ret++;
        if(p-i>=n) ans=min(ans,ret);
    }
    if(ans==1e9) cout<<"impossible\n";
    else cout<<ans<<'\n';
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin>>n>>m){
        solve();
    }
    return 0;
}
