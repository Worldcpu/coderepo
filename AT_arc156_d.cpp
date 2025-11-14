#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2025;
int f[50][MN],ans,n,K,a[MN];

void calc(int x){
    int ret=1;
    for(int j=x+1;j<50;j++){
        if((K>>j)&1) ret=ret*n%2;
    }
    if(!ret) return;
    for(int j=0;j<MN;j++){
        if((j&1)&&f[x][j]) ans^=1ll<<x; 
    }
}

signed main(){
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    if(K&1){
        for(int i=1;i<=n;i++) f[0][a[i]]^=1;
    }else f[0][0]=1;
    calc(0);
    for(int i=1;i<50;i++){
        if(!((K>>i)&1)){
            for(int j=0;j<MN;j++){
                f[i][j>>1]^=f[i-1][j];
            }
        }else{
            for(int j=0;j<MN;j++){
                for(int k=1;k<=n;k++){
                    f[i][(j>>1)+a[k]]^=f[i-1][j];
                }
            }
        }
        calc(i);
    }
    cout<<ans;

    return 0;
}