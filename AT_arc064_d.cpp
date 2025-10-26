#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=1e9+7;
int n,K,f[MN],ans;
vector<int> vct;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>K;
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            vct.push_back(i);
            if(i*i!=n){
                vct.push_back(n/i);
            }
        }
    }
    sort(vct.begin(),vct.end());
    for(int i=0;i<vct.size();i++){
        f[i]=ksm(K,(vct[i]+1)>>1);
        for(int j=0;j<i;j++){
            if(vct[i]%vct[j]==0){
                f[i]=(f[i]-f[j]+MOD)%MOD;
            }
        }
        ans=(ans+f[i]*(vct[i]%2?vct[i]:vct[i]>>1%MOD))%MOD;
    }
    cout<<ans;
    return 0;
}