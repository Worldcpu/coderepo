#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15,MOD=19940417;
int f[MN][2],b[MN],ans,top,n,K;
pir pos[MN];

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
    for(int i=1;i<=K;i++){
        cin>>pos[i].first>>pos[i].second;
    }
    pos[++K].first=n;
    pos[++K].first=0;
    sort(pos+1,pos+1+K);
    K=unique(pos+1,pos+1+K)-pos-1;
    f[1][1]=1;
    for(int i=2;i<=K;i++){
        int len=pos[i].first-pos[i-1].first-pos[i].second-pos[i-1].second;
        if(pos[i].first-pos[i-1].first==pos[i].second-pos[i-1].second){
            f[i][0]=(f[i-1][0]+f[i][0])%MOD;
            if(pos[i-1].second==0) f[i][0]=(f[i][0]+f[i-1][1])%MOD; 
        }
        else if(pos[i].first-pos[i-1].first==pos[i-1].second-pos[i].second){
            f[i][1]=(f[i][1]+f[i-1][1]+f[i-1][0])%MOD;
        }
        else if(len<0){
            f[i][1]=(f[i][1]+f[i-1][0])%MOD;
        }
        else if(len==0){
            f[i][1]=(f[i][1]+f[i-1][0])%MOD;
            f[i][0]=(f[i][0]+f[i-1][0]+f[i-1][1])%MOD;
        }else{
            int p=(f[i-1][0]*2+f[i-1][1])*ksm(2,len/2-1)%MOD;
            f[i][1]=(f[i][1]+p)%MOD;
            if(pos[i].second>0) f[i][0]=(f[i][0]+p)%MOD;
        }
        if(f[i][1]>0) ans=max(ans,pos[i].first-pos[i-1].first+pos[i].second+pos[i-1].second);
    }
    cout<<f[K][1]<<' '<<ans/2;
    return 0;
}
