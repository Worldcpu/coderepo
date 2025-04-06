#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MOD=1e9+7;
constexpr int MH=2e5+15,MN=2048;
struct Node
{
    int x,y;
}nd[MN];
int h,w,n;
ll jc[MH],inv[MH],f[MN];

ll ksm(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1){
            ret=(ret*a)%MOD;
        }
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void getinv(){
    jc[0]=1;
    for(int i=1;i<=2e5;i++){
        jc[i]=(i*jc[i-1])%MOD;
    }

    inv[200000]=ksm(jc[200000],MOD-2);
    for(int i=2e5-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

ll getC(ll a,ll b){
    return jc[a]*inv[b]%MOD*inv[a-b]%MOD;
}

bool cmp(Node a,Node b){
    if(a.x==b.x) return a.y<b.y;
    else return a.x<b.x;
}

int main(){
    getinv();
    cin>>h>>w>>n;
    for(int i=1;i<=n;i++){
        cin>>nd[i].x>>nd[i].y;
    }
    sort(nd+1,nd+1+n,cmp);
    nd[n+1].x=h;
    nd[n+1].y=w;
    for(int i=1;i<=n+1;i++){
        f[i]=getC(nd[i].x+nd[i].y-2,nd[i].x-1);
        for(int j=1;j<i;j++){
            if(nd[j].x>nd[i].x||nd[j].y>nd[i].y) continue;
            f[i]=(f[i]-f[j]*getC(nd[i].x-nd[j].x+nd[i].y-nd[j].y,nd[i].x-nd[j].x))%MOD;
        }
    }
    cout<<(f[n+1]+MOD)%MOD;
    return 0;
}