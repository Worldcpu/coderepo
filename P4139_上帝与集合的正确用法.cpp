#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15;
int phi[MN],p[MN],cnt,MOD;
bool vis[MN];

void getphi(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            p[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*p[j]<=n;j++){
            vis[i*p[j]]=1;
            if(!(i%p[j])){
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }else phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
}


int ksm(int a,int b,int MOD){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int solve(int p){
    if(p==1) return 0;
    return ksm(2,solve(phi[p])+phi[p],p);
}

signed main(){
    getphi(1e7);
    int T;
    cin>>T;
    while(T--){
        cin>>MOD;
        cout<<solve(MOD)<<'\n';
    }
    return 0;
}
