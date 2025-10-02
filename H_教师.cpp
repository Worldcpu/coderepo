#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=(1<<15)+15,MM=55;
int n,m,K,T,v[MM][MN],f[MM][MN],g[MN],val[MM];

signed main(){
    cin>>n>>m>>K>>T;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=K;j++){
            cin>>v[i][j];
        }
    }
    for(int s=0;s<(1<<n);s++){
        int ret=0;
        for(int j=1;j<=n;j++){
            if((s>>(j-1))&1){
                ret+=v[j][0];
            }
        }
        for(int i=0;i<=T;i++){
            f[i][s]=ret;
        }
    }
    for(int qwq=1;qwq<=m;qwq++){
        int h,t;
        cin>>h>>t;
        for(int i=1;i<=n;i++){
            val[i]=v[i][0];
        }
        for(int i=1;i<=h;i++){
            int x,y;
            cin>>x>>y;
            val[x]=v[x][y];
        }
        for(int i=T-t;i>=0;i--){
            memcpy(g,f[i],sizeof(f[i]));
            for(int s=0;s<(1<<n);s++){
                for(int j=1;j<=n;j++){
                    if(!((s>>(j-1))&1)){
                        g[s|(1<<j-1)]=max(g[s|(1<<j-1)],g[s]+val[j]);
                    }
                }
            }
            for(int s=0;s<(1<<n);s++){
                f[i+t][s]=max(f[i+t][s],g[s]);
            }
        }
    }
    for(int i=1;i<=T;i++){
        cout<<f[i][(1<<n)-1]<<'\n';
    }
    return 0;
}
