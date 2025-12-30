#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,INF=1e18,MOD=998244353;
int f[MN],n,Y[MN];
bool vis[MN];


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        Y[x]=y;
    }
    f[0]=1;
    Y[0]=INF,Y[n+1]=-INF;
    for(int i=1;i<=n+1;i++){
        for(int j=0;j<i;j++){
            if(Y[j]<Y[i]){
                continue;
            }
            int mn=Y[j],flg=1;
            for(int k=j+1;k<i;k++) vis[k]=0;
            for(int k=j+1;k<i;k++){
                if(Y[k]<Y[i]||Y[k]>Y[j]) continue;
                if(mn<Y[k]) vis[k]=1;
                else mn=Y[k];
            }
            mn=Y[i];
            for(int k=i-1;k>=j+1;k--){
                if(Y[k]<Y[i]||Y[k]>Y[j]) continue;
                if(mn>Y[k]) vis[k]=1;
                else mn=Y[k];
                flg&=vis[k];
            }
            f[i]=(f[i]+f[j]*flg)%MOD;
        }
    }
    cout<<f[n+1];
    return 0;
}