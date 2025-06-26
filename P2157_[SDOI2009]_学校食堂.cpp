#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520,MS=1<<8,INF=0x3f3f3f3f;
int T,n,f[MN][MS][MS],a[MN],b[MN];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    memset(f,0x3f,sizeof(f));
    f[1][0][7]=0;
    for(int i=1;i<=n;i++){
        for(int s=0;s<(1<<8);s++){
            for(int j=-8;j<=7;j++){
                if(f[i][s][j+8]!=INF){
                    if(s&1){
                        f[i+1][s>>1][j+7]=min(f[i+1][s>>1][j+7],f[i][s][j+8]);
                    }else{
                        int lim=INF;
                        for(int h=0;h<8;h++){
                            if(!(s&(1<<h))){
                                if(i+h>lim) break;
                                lim=min(lim,i+h+b[i+h]);
                                f[i][s|(1<<h)][h+8]=min(f[i][s|(1<<h)][h+8],f[i][s][j+8]+(i+j?(a[i+j]^a[i+h]):0));
                            }
                        }
                    }
                }
            }
        }
    }
    int ans=INF;
    for(int i=0;i<=8;i++){
        ans=min(ans,f[n+1][0][i]);
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
