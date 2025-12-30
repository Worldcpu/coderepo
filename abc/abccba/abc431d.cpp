#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MV=501;
int f[MN],n,h[MN],b[MN],w[MN],sumw,sumb,limw;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>h[i]>>b[i];
        sumw+=w[i];
        sumb+=b[i];
    }
    memset(f,128,sizeof(f));
    limw=sumw>>1;
    f[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=limw;j>=w[i];j--){
            f[j]=max(f[j],f[j-w[i]]+h[i]-b[i]);
        }
    }
    cout<<sumb+(*max_element(f,f+1+limw));
    
    return 0;
}
