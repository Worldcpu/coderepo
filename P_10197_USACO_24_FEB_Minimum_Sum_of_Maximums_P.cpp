#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,INF=1e8;
int n,K,mk,tot,ans,a[MN],b[MN],x[MN],L[MN],R[MN],len[MN],cnt[MN],f[MN][MN][MN];
bool vis[MN];

signed main(){
    memset(f,0x3f,sizeof(f));
    cin>>n>>K;
    for(int i=1;i<=n;i++) cin>>a[i];
    a[0]=a[n+1]=INF;
    for(int i=1;i<=K;i++){
        cin>>x[i];
        vis[x[i]]=1;
    }
    x[++K]=n+1;
    mk=1<<K;
    for(int i=1;i<=K;i++){
        L[i]=x[i-1];
        R[i]=x[i];
        len[i]=R[i]-L[i]-1;
    }
    for(int i=1;i<=K;i++){
        if(len[i]==0){
            ans+=max(a[L[i]],a[R[i]]);
            continue;
        }
        if(a[L[i]]<=a[R[i]]){
            for(int j=L[i];j<R[i];j++){
                ans+=a[j];
            }
        }else{
            for(int j=L[i]+1;j<=R[i];j++){
                ans+=a[j];
            }
            swap(L[i],R[i]);
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]) b[++tot]=a[i];
    }
    sort(b+1,b+1+tot);
    for(int i=0;i<mk;i++){
        for(int j=1;j<=K;j++){
            if(i&(1<<(j-1))) cnt[i]+=len[j];
        }
    }
    for(int l=1;l<=tot;l++){
        for(int r=1;r<=tot;r++) f[l][r][0]=0;
    }
    for(int s=1;s<mk;s++){
        for(int ln=cnt[s];ln<=tot;ln++){
            for(int l=1,r=ln;r<=tot;l++,r++){
                f[l][r][s]=min(f[l+1][r][s],f[l][r-1][s]);
                for(int i=1;i<=K;i++){
                    if(len[i]==1&&(s&(1<<(i-1)))){
                        f[l][r][s]=min(f[l][r][s],f[l+1][r][s-(1<<(i-1))]+max(a[R[i]],b[l])-min(a[L[i]],b[l]));
                        f[l][r][s]=min(f[l][r][s],f[l][r-1][s-(1<<(i-1))]+max(a[R[i]],b[r])-min(a[L[i]],b[r]));
                    }
                }
                for(int s1=s&(s-1);s1!=0;s1=s&(s1-1)){
                    f[l][r][s]=min(f[l][r][s],f[l][l+cnt[s1]-1][s1]+f[l+cnt[s1]][r][s-s1]);
                }
                if(l!=r){
                    for(int i=1;i<=K;i++){
                        if(len[i]!=1&&(s&(1<<(i-1)))){
                            f[l][r][s]=min(f[l][r][s],f[l+1][r-1][s-(1<<(i-1))]+max(a[R[i]],b[r])-min(a[L[i]],b[l]));
                        }
                    }
                }
            }
        }
    }
    int t=0;
    for(int i=1;i<=K;i++) if(len[i]) t+=(1<<(i-1));
    cout<<ans+f[1][tot][t]-a[0]*2;
    cerr<<t<<" "<<ans<<" "<<f[1][tot][t];
    return 0;
}