#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e4+15,MM=55,MOD=1e9+7;
int T,h,w,m,n,cntx,cnty,ans,pos[MM][5],arr[MM][MM],x[MN],y[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void solve(){
    cin>>h>>w>>m>>n;
    cntx=cnty=ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<5;j++){
            cin>>pos[i][j];
        }
        x[++cntx]=pos[i][0];
        x[++cntx]=++pos[i][2];
        y[++cnty]=pos[i][1];
        y[++cnty]=++pos[i][3];
    }
    x[++cntx]=1;
    x[++cntx]=w+1;
    y[++cnty]=1;
    y[++cnty]=h+1;
    sort(x+1,x+1+cntx);
    sort(y+1,y+1+cnty);
    cntx=unique(x+1,x+1+cntx)-x-1;
    cnty=unique(y+1,y+1+cnty)-y-1;
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<cntx;j++){
            for(int k=1;k<cnty;k++){
                arr[j][k]=m;
            }
        }
        for(int p=1;p<=n;p++){
            for(int j=lower_bound(x+1,x+1+cntx,pos[p][0])-x;x[j]!=pos[p][2];j++){
                for(int k=lower_bound(y+1,y+1+cnty,pos[p][1])-y;y[k]!=pos[p][3];k++){
                    arr[j][k]=min(arr[j][k],pos[p][4]-(i>>(p-1)&1));
                }
            }
        }
        int tmp=1;
        for(int j=1;j<cntx;j++){
            for(int k=1;k<cnty;k++){
                tmp=1ll*tmp%MOD*ksm(arr[j][k],(x[j+1]-x[j])*(y[k+1]-y[k]))%MOD;
            }
        }
        ans=(ans+tmp*(__builtin_popcount(i)&1?-1:1)+MOD)%MOD;
    }
    cout<<ans<<'\n';
}

signed main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
