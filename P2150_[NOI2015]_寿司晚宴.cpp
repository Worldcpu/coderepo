#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MS=1<<9,MN=520;
const int prime[9]= {2,3,5,7,11,13,17,19};
int g[3][MS][MS],f[MS][MS],pw[MN],n,MOD;
pir a[MN];

void init(){
    pw[0]=1;
    for(int i=1;i<=20;i++) pw[i]=pw[i-1]*2;
    for(int i=2;i<=n;i++){
        int x=i;
        for(int j=0;j<8;j++){
            if(x%prime[j]==0) a[i].second|=pw[j];
            while(x%prime[j]==0) x/=prime[j];
        }
        a[i].first=x;
    }
}

signed main(){
    cin>>n>>MOD;
    init();
    sort(a+2,a+1+n);
    f[0][0]=1;
    for(int i=2;i<=n;i++){
        if(a[i].first==1||a[i].first!=a[i-1].first||i==2){
            memcpy(g[1],f,sizeof(g[1]));
            memcpy(g[2],f,sizeof(g[2]));
        }
        for(int s1=255;s1>=0;s1--){
            for(int s2=255;s2>=0;s2--){
                if(s1&s2) continue;
                if(!(s2&a[i].second)) g[1][s1|a[i].second][s2]=(g[1][s1|a[i].second][s2]+g[1][s1][s2])%MOD;
                if(!(s1&a[i].second)) g[2][s1][s2|a[i].second]=(g[2][s1][s2|a[i].second]+g[2][s1][s2])%MOD;
            }
        }
        if(i==n||a[i].first!=a[i+1].first||a[i].first==1){
            
            for(int s1=255;s1>=0;s1--){
                for(int s2=255;s2>=0;s2--){
                    if(s1&s2) continue;
                    f[s1][s2]=(g[1][s1][s2]+g[2][s1][s2]-f[s1][s2]+MOD)%MOD;
                }
            }
        }
    }
    int ans=0;

    for(int s1=255;s1>=0;s1--){
        for(int s2=255;s2>=0;s2--){
            (ans+=f[s1][s2])%=MOD;
        }
    }
    cout<<ans;
    return 0;
}
