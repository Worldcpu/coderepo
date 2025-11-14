#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=10,MK=1e5+15;
int n,m,w[MN],L[MK],v[MK],len[1<<10],mxw,f[MN][MN],p[MN],ans=1e18;

void solve(){
    for(int i=1;i<=n;i++){
        int tmp=(1<<p[i]-1);
        for(int j=i+1;j<=n;j++){
            tmp+=(1<<p[j]-1);
            f[i][j]=len[tmp];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=i+2;j<=n;j++){
            for(int k=i+1;k<=j-1;k++){
                f[i][j]=max(f[i][j],f[i][k]+f[k][j]);
            }
        }
    }
    ans=min(ans,f[1][n]);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
        mxw=max(mxw,w[i]);
    }
    for(int i=1;i<=m;i++){
        cin>>L[i]>>v[i];
        if(mxw>v[i]){
            cout<<-1;
            return 0;
        }
    }
    for(int st=0;st<(1<<n);st++){
        if(__builtin_popcount(st)>1){
            int cnt=0;
            for(int j=1;j<=n;j++){
                if((st>>(j-1))&1){
                    cnt+=w[j];
                }
            }
            for(int j=1;j<=m;j++){
                if(cnt>v[j]) len[st]=max(len[st],L[j]);
            }
        }
    }
    for(int i=1;i<=n;i++) p[i]=i;
    do{
        solve();
    }while(next_permutation(p+1,p+1+n));
    cout<<ans;
    return 0;
}