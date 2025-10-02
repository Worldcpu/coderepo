#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=62;
int n,m,K,MOD,pw[MN+5];

namespace DP{
    pir f[MN+5][2][2][2];
    bool vis[MN+5][2][2][2];

    pir dfs(int pos,bool limn,bool limm,bool limk){
        if(pos==-1) return pir(1,0);
        if(vis[pos][limn][limm][limk]) return f[pos][limn][limm][limk];
        int upn,upm,posk=(K>>pos)&1;
        if(limn){
            upn=(n>>pos)&1;
        }else upn=1;
        if(limm) upm=(m>>pos)&1;
        else upm=1;
        auto ret=pir(0,0);
        for(int i=0;i<=upn;i++){
            for(int j=0;j<=upm;j++){
                if(limk&&(i^j)<posk) continue;
                auto res=dfs(pos-1,limn&&(i==upn),limm&&(j==upm),limk&&((i^j)==posk));
                ret.first=(ret.first+res.first)%MOD;
                ret.second=(ret.second+res.first*(i^j)*pw[pos]%MOD+res.second)%MOD;
            }
        }
        f[pos][limn][limm][limk]=ret;
        vis[pos][limn][limm][limk]=1;
        return f[pos][limn][limm][limk];
    }

    int calc(){
        memset(vis,0,sizeof(vis));
        pw[0]=1;
        for(int i=1;i<=MN;i++){
            pw[i]=pw[i-1]*2%MOD;
        }
        auto ret=dfs(MN,1,1,1);
        K%=MOD;
        return (ret.second-ret.first*K%MOD+MOD)%MOD;
    }
}

void solve(){
    cin>>n>>m>>K>>MOD;
    n--,m--;
    cout<<DP::calc()<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}