#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MM=4e6+15,MOD=998244353;
int n,m,sum[MM],cntv[MM],pos[MM],cnty,ans,res[MN][MN],cnts[MM];
char mp[MN][MN];

int calc(int K){
    if(K>n) return 0;
    int len=cnty/K,ret=1;
    for(int i=1;i<=K;i++){
        ret=ret*cntv[i*len]%MOD;
    }
    if(!ret) return 0;
    for(int i=1;i<=K;i++){
        int l=pos[(i-1)*len]+1, r=pos[i*len];
        for(int j=1;j<=m;j++){
            res[i][j]=res[i][j-1];
            for(int k=l;k<=r;k++){
                res[i][j]+=(mp[k][j]=='Y');
            }
        }
    }

    for(int j=1;j<=m;j++){
        int base=res[1][j];
        bool ok=true;
        for(int i=1;i<=K;i++){
            if(res[i][j]!=base){
                ok=false;
                break;
            }
        }
        if(ok) cnts[base]++;
    }

    cnts[len]=1;
    for(int i=1;i<=(len>>1);i++){
        ret=ret*cnts[i*2]%MOD;
    }

    for(int i=1;i<=m;i++){
        cnts[res[1][i]]=0;
    }
    return ret;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            sum[i]+=mp[i][j]=='Y';
            cnty+=mp[i][j]=='Y';
        }
    }

    for(int i=1;i<=n;i++){
        sum[i]+=sum[i-1];
        pos[sum[i]]=i;
        cntv[sum[i]]++;
    }
    cntv[cnty]=1;

    if(cnty&1){
        cout<<0<<'\n';
        return 0;
    }

    for(int i=1;i<=(cnty>>1);i++){
        if((cnty>>1)%i==0){
            ans=(ans+calc(i))%MOD;
        }
    }

    cout<<ans<<'\n';
    return 0;
}
