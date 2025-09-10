#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MM=20,MOD=1e9+7;
int n,num[MN],a[MM][MM],mp[MM][MN][2],MAXN,ans;

namespace HLS{

    int solve(){
        int ret=1;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                while(a[j][i]){
                    int div=a[i][i]/a[j][i];
                    for(int k=i;k<=n;k++){
                        a[i][k]=(a[i][k]-div*a[j][k]%MOD+MOD)%MOD;
                    }
                    swap(a[i],a[j]);
                    ret*=-1;
                }
            }
            ret=ret*a[i][i]%MOD;
        }
        return (ret%MOD+MOD)%MOD;
    }
}

void add(int x,int y){
    a[x][x]++;
    a[y][y]++;
    a[x][y]--;
    a[y][x]--;
}

signed main(){
    cin>>n;
    n--;
    for(int i=1;i<=n;i++){
        cin>>num[i];
        for(int j=1;j<=num[i];j++){
            int u,v;
            cin>>u>>v;
            mp[i][j][0]=u;
            mp[i][j][1]=v;
        }
    }
    for(int s=1;s<(1<<n);s++){
        memset(a,0,sizeof(a));
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(!(s&(1<<(i-1)))) continue;
            cnt++;
            for(int j=1;j<=num[i];j++){
                add(mp[i][j][0],mp[i][j][1]);
            }
        }
        ans=(ans+((n-cnt)&1?-1:1)*HLS::solve()%MOD+MOD)%MOD;
    }
    cout<<ans;
    return 0;
}
