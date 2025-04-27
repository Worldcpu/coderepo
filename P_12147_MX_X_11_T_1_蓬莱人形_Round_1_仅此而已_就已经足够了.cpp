#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=35;
ll p[MN],s[MN][MN],n,k,g,m,ans,now;
int T;

void solve(){
    cin>>n>>k;
    if(n<(1ll<<k)){
        cout<<(1ll<<k)*(n+1)<<'\n';
        return;
    }
    g=0;
    for(int i=0;i<=k-1;i++){
        g+=(((n>>i)&1)<<i);
    }
    n-=g;
    g++;
    m=(n>>k);
    ans=now=0;
    for(int i=0;i<MN;i++){
        if(now>=n) break;
        ll l=0,r=(1ll<<(MN-1));
        ll t=(now>>k);
        while(l<r){
            ll mid=((l+r)>>1)+1;
            ll q=(mid<<(i+1))+t;
            if(q<m) l=mid;
            else r=mid-1;
        }
        ans+=(l+1)*(1ll<<k)*s[k][i];
        now+=(1ll<<(k+i));
    }
    int cnt=0;
    while(m){
        if(m&1) cnt++,m>>=1;
        else break;
    }
    ans+=s[k][cnt]*g;
    cout<<ans<<'\n';
}

int main(){
    p[0]=1;
    for(int i=1;i<MN;i++){
        p[i]=(1<<i);
        p[i]+=p[i-1];
    }
    for(int i=0;i<MN;i++){
        for(int j=0;j<MN;j++){
            if(i+j>=MN) break;
            if(i==0) s[i][j]=p[i+j];
            s[i][j]=p[i+j]-p[i-1];
        }
    }
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}