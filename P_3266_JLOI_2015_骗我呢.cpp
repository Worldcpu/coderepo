#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e6+15,MOD=1e9+7;
int n,m,x,y,pw[MN],inv[MN],ans;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void flipa(){
    swap(x,y);
    x--;
    y++;
}

void flipb(){
    swap(x,y);
    x+=m+2;
    y-=m+2;
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
}

int getC(int a,int b){
    if(a<b||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int calc(int x,int y){
    if(x<0||y<0) return 0;
    return getC(x+y,x);
}

signed main(){
    initpw();
    cin>>n>>m;
    x=n+m+1,y=n;
    ans=calc(x,y);
    while(x>=0&&y>=0){
        flipa();
        ans=(ans-calc(x,y)+MOD)%MOD;
        flipb();
        ans=(ans+calc(x,y))%MOD;
    }
    x=n+m+1,y=n;
    while(x>=0&&y>=0){
        flipb();
        ans=(ans-calc(x,y)+MOD)%MOD;
        flipa();
        ans=(ans+calc(x,y))%MOD;
    }
    cout<<ans;
    return 0;
}