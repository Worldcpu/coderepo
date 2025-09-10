#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15,MOD=998244353;
int n,m,x,y,pw[MN],inv[MN],pre[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int getC(int a,int b){
    if(a<b||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
    for(int i=0;i<MN;i++){
        if(i) pre[i]=pre[i-1];
        if(!((n-i-1)&1)){
            pre[i]=(pre[i]+getC(n-1,(n-1-i)>>1))%MOD;
        }
    }
}

int calc(int l,int r){
    if(l<0&&r>0) return (calc(0,r)+calc(1,-l))%MOD;
    if(l<0){
        swap(l,r);
        l=-l,r=-r;
    }
    int ret=pre[r];
    if(l) ret=(ret-pre[l-1]+MOD)%MOD;
    return ret;
}

int calc(int x){
    int l=max(1-n,0-x),r=min(n-1,m-x);
    if(l>r) return 0;
    return calc(l,r);
}

void flipa(){
    swap(x,y);
    x=-x-2;
    y=-y+2*(m+1);
}

signed main(){
    cin>>n>>m;
    initpw();
    m=(m+1)/2;
    int ans=calc(1);
    x=y=1;
    for(int i=0;i<=(n+m-1)/m;i++){
        flipa();
        if(i&1) ans=(ans+calc(x)+calc(y))%MOD;
        else ans=(ans-calc(x)-calc(y)+MOD)%MOD;
    }
    cout<<ans;
    return 0;
}