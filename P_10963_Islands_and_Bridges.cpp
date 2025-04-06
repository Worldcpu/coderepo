#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MN=14;
int T;
int f[MN][MN][1<<MN],g[MN][MN][1<<MN],v[MN],n,m;
bool mp[MN][MN];
void solve(){
    memset(v,0,sizeof(v));
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    memset(mp,0,sizeof(mp));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        mp[u][v]=mp[v][u]=1;
    }
    if(n==1){
        cout<<v[1]<<" "<<1<<'\n';
        return;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j||!mp[i][j]) continue;
            f[i][j][(1<<(i-1))|(1<<(j-1))]=v[i]*v[j]+v[i]+v[j];
            g[i][j][(1<<(i-1))|(1<<(j-1))]=1;
        }
    }
    for(int i=0;i<1<<n;i++){
        for(int j=1;j<=n;j++){
            if(!((i>>(j-1))&1)) continue;
            for(int k=1;k<=n;k++){
                if(j==k||!mp[j][k]||!((i>>(k-1))&1)) continue;
                for(int p=1;p<=n;p++){
                    if(!((i>>(p-1))&1)||j==p||k==p||!mp[k][p]||!g[k][p][i^(1<<(j-1))]) continue;
                    int val=f[k][p][i^(1<<(j-1))]+v[j]+v[j]*v[k]+(mp[j][p])*v[j]*v[k]*v[p];
                    if(val==f[j][k][i]) g[j][k][i]+=g[k][p][i^(1<<(j-1))];
                    else if(val>f[j][k][i]){
                        f[j][k][i]=val;
                        g[j][k][i]=g[k][p][i^(1<<(j-1))];
                    }
                }
            }
        }
    }
    int ans=0,cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!mp[i][j]||!g[i][j][(1<<n)-1]||i==j) continue;
            if(ans<f[i][j][(1<<n)-1]){
                ans=f[i][j][(1<<n)-1];
                cnt=g[i][j][(1<<n)-1];
            }else if(ans==f[i][j][(1<<n)-1]){
                cnt+=g[i][j][(1<<n)-1];
            }
        }
    }
    cout<<ans<<" "<<(cnt>>1)<<'\n';
}
signed main(){
    cin>>T;
    while (T--)
    {
        solve();
    }
    
    return 0;
}