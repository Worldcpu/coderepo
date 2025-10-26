#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=1e9+7,MN=50,MS=1<<20;
int f[MN][MS],ans,n,x,y,z,goal,slim;

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
    cin>>n>>x>>y>>z;
    slim=(1<<x+y+z)-1;
    goal|=1<<x+y+z-1;
    goal|=1<<y+z-1;
    goal|=1<<z-1;
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int s=0;s<=slim;s++){
            int to;
            for(int k=1;k<=10;k++){
                to=(s<<k)|(1<<k-1);
                to&=slim;
                if((to&goal)==goal) continue;
                f[i][to]=(f[i][to]+f[i-1][s])%MOD;
            }
        }
    }
    ans=ksm(10,n);   
    for(int i=0;i<=slim;i++){
        ans=(ans-f[n][i]+MOD)%MOD;
    }
    cout<<ans;

    return 0;
}