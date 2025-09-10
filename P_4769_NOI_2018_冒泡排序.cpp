#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5000005,MOD=998244353;
int pw[MN],inv[MN],n,q[MN],ans,mn,mx;
bool vis[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b||b<0) return 0; 
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void init(){
    ans=0;
    mx=0;
    mn=1;
    memset(vis,0,sizeof(vis));
}

int F(int x,int y){
    if(x>y||y>n) return 0;
    return (getC((n<<1)-x-y,n-x)-getC((n<<1)-x-y,n-x+1)+MOD)%MOD;
}

void solve(){
    cin>>n;
    init();
    bool flag=0;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        if(flag) continue;
        mx=max(mx,v);
        ans=(ans+F(i-1,mx+1))%MOD;
        vis[v]=1;
        while(vis[mn]) mn++;
        if(mn<v&&v<mx) flag=1;
    }
    cout<<ans<<'\n';
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    initpw();
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
