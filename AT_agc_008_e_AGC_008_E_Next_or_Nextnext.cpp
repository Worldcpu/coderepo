#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15,MOD=1e9+7;
int n,ans,a[MN],dg[MN],f[MN],cir[MN],ftl[MN],sum[MN];
int vis[MN];

void initcir(int x){
    int now=0,fpos=0,ed=0,frl=0;
    while(cir[x]){
        now++;
        cir[x]=0;
        if(ftl[x]){
            if(!fpos) ed=fpos=now,frl=ftl[x];
            else{
                int kl=(ftl[x]<now-ed)+(ftl[x]<=now-ed);
                ans=1LL*ans*kl%MOD;
                ed=now;
            }
        }
        x=a[x];
    }
    if(!fpos) sum[now]++;
    else{
        int k=(frl<now-ed+fpos)+(frl<=now-ed+fpos);
        ans=1LL*ans*k%MOD;
    }
}

void solve(){
    for(int i=1;i<=n;i++){
        if(dg[i]) continue;
        int x=i,len=0;
        for(;!cir[x];x=a[x]) len++;
        ftl[x]=len;
    }
    ans=1;
    for(int i=1;i<=n;i++) if(cir[i]) initcir(i);
    for(int i=1;i<=n;i++){
        if(!sum[i]) continue;
        for(int j=0;j<=sum[i];j++) f[j]=0; 
        f[0]=1;
        for(int j=1;j<=sum[i];j++){
            if(i>1&&(i&1)) f[j]=f[j-1]*2%MOD;
            else f[j]=f[j-1];
            if(j>1) f[j]=(f[j]+1LL*f[j-2]*(j-1)%MOD*i%MOD)%MOD;
        }
        ans=1LL*ans*f[sum[i]]%MOD;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        dg[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;
        int x=i;
        for(;!vis[x];x=a[x]) vis[x]=i;
        if(vis[x]!=i) continue;
        for(;!cir[x];x=a[x]) cir[x]=1;
    }
    for(int i=1;i<=n;i++){
        if((cir[i]&&dg[i]>2)||(!cir[i]&&dg[i]>1)){
            cout<<0;
            return 0;
        }
    }
    solve();
    cout<<ans;
    return 0;
}
