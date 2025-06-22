#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,MOD=1e4;
int nxt[MN],n,T,K,f[MN],a[MN];


int main(){
    cin>>n>>T;
    n%=MOD;
    while(T--){
        cin>>K;
        for(int i=1;i<=K;i++){
            cin>>a[i];
            f[i]=nxt[i]=0;
        }
        int ans=0;
        for(int i=2,p=0;i<=K;i++){
            while(p&&a[p+1]!=a[i]) p=nxt[p];
            if(a[p+1]==a[i]) nxt[i]=p+1,p=nxt[i];
        }
        for(int i=K;i>=1;i=nxt[i]) f[i]=1;
        for(int i=1,j=n;i<=K;i++,j=j*n%MOD){
            if(f[i]) ans=(ans+j)%MOD;
        }
        printf( "%04d\n", ans );
    }



    return 0;
}
