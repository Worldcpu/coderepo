#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1<<19,MOD=1e9+7,INF=1e18;
int pw[MN],pwf[MN],n,a[MN],cf[MN],b[MN],btot,sum[MN],cnt[MN];
pir f[MN];

int lowbit(int x){
    return x&-x;
}

int high(int x){return (!x)?-1:(31-__builtin_clz(x));}

int ksm(int a,int b){
    int ret=1;
    while(b>0){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pwf[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=ksm(i,i-2);
        pwf[i]=pwf[i-1]*i%MOD;
    }
}

pir merge(pir x,pir y,int v,int k){
    if(x.first==y.first+v){
        x.second=(x.second+y.second*k)%MOD;
    }else if(x.first>y.first+v){
        x.first=y.first+v;
        x.second=y.second*k%MOD;
    }
    return x;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        cf[i]=a[i+1]-a[i];
    }
    for(int i=1;i<n;i++){
        if(cf[i]){
            b[++btot]=cf[i];
        }
    }
    f[0]=pir(0,1);
    for(int s=1;s<(1<<btot);s++){
        int pos=32-__builtin_clz(lowbit(s));
        sum[s]=sum[s&(s-1)]+b[pos];
        cnt[s]=cnt[s&(s-1)]+1;
        f[s].first=INF;
    }
    for(int s=0;s<(1<<btot);s++){
        int rst=((1<<btot)-1)^s;
        for(int ss=rst;ss;ss=(ss-1)&rst){
            if(high(ss)<high(s)) break;
            if(!sum[ss]){
                f[s|ss]=merge(f[s|ss],f[s],cnt[ss]-1,pw[cnt[ss]]);
            }else{
                f[s|ss]=merge(f[s|ss],f[s],cnt[ss],2*pw[cnt[ss]]%MOD*cnt[ss]%MOD);
            }
        }
    }
    cerr<<f[(1<<btot)-1].first;
    cout<<f[(1<<btot)-1].first<<'\n'<<f[(1<<btot)-1].second*pwf[f[(1<<btot)-1].first];

    return 0;
}