#include<bits/stdc++.h>
using namespace std;
constexpr int MS=(1<<17),MK=17,MN=1e5+15;
int f[MS],g[MS],c[MN],sum[MN],v[MK],ans,K,n;
bool flag=0;

int getp(int l,int r,int k){
    int p=sum[l],ans=l;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sum[mid]-p<=k){
            ans=mid;
            l=mid+1;
        }else r=mid-1;
    }
    return ans;
}

int main(){
    cin>>K>>n;
    for(int i=1;i<=K;i++){
        cin>>v[i];
    }
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+c[i];
    }
    for(int i=0;i<(1<<K);i++){
        for(int j=1;j<=K;j++){
            if((i&(1<<(j-1)))) continue;
            f[i|(1<<(j-1))]=max(f[i|(1<<(j-1))],getp(f[i],n,v[j]));
        }
        if(f[i]==n){
            flag=1;
            int ret=0;
            for(int j=1;j<=K;j++){
                if(i&(1<<(j-1))){
                    continue;
                }
                ret+=v[j];
            }
            ans=max(ans,ret);
        }
    }
    if(!flag) cout<<-1;
    else cout<<ans;
    return 0;
}
