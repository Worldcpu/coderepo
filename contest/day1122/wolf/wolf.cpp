#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7,INF=1e18;
int n,m,wx[MN],wy[MN],pw[MN],inv[MN],ans;

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

// namespace Sub1{
//     constexpr int VL=-2e2,VR=2e2;

//     int dis(int x1,int y1,int x2,int y2){
//         return abs(x1-x2)+abs(y1-y2);
//     }

//     // (x1,y1) -> (x2,y2) 的方案数
//     int getF(int n,int x,int y){
//         if((n+x+y)&1) return 0;
//         if(n<x+y) return 0;
//         int t=(x+y+n)/2;
//         return getC(n,t)*getC(n,t-x)%MOD;
//     }


//     bool check(int x,int y){
//         for(int i=1;i<=n;i++){
//             int d=dis(x,y,wx[i],wy[i]);
//             if(d>m) return 0;
//         }
//         return 1;
//     }

//     void solve(){
//         for(int x=VL;x<=VR;x++){
//             for(int y=VL;y<=VR;y++){
//                 if(!check(x,y)) continue;
//                 int res=1;
//                 for(int j=1;j<=n;j++){
//                     int tmp=getF(m,abs(x-wx[j]),abs(y-wy[j]));
//                     // cerr<<tmp<<'\n';
//                     res=res*tmp%MOD;
//                 }
//                 ans=(ans+res)%MOD;
//             }
//         }
//         cout<<ans<<'\n';
//     }

// }

namespace Sub2{
    int X[MN],Y[MN],dw[2],up[2];

    int solx(int hx,int k){
        int ret=1;
        for(int i=1;i<=n;i++){
            if(abs(hx-X[i])>m||(k+X[i]-hx)%2!=0){
                ret=0;
                break;
            }
            ret=ret*getC(k,(k+X[i]-hx)/2)%MOD;
        }
        return ret;
    }

    int soly(int hy,int k){
        int ret=1;
        for(int i=1;i<=n;i++){
            if(abs(hy-Y[i])>m||(k+Y[i]-hy)%2!=0){
                ret=0;
                break;
            }
            ret=ret*getC(k,(k+Y[i]-hy)/2)%MOD;
        }
        return ret;
    }

    void solve(){
        dw[0]=dw[1]=-INF;
        up[0]=up[1]=INF;
        for(int i=1;i<=n;i++){
            X[i]=wx[i]+wy[i];
            Y[i]=wx[i]-wy[i];
            dw[0]=max(dw[0],X[i]-m);
            dw[1]=max(dw[1],Y[i]-m);
            up[0]=min(up[0],X[i]+m);
            up[1]=min(up[1],Y[i]+m);
        }
        if(up[0]<dw[0]||up[1]<dw[1]){
            cout<<0<<'\n';
            return;
        }
        int ansx=0,ansy=0;
        for(int x=dw[0];x<=up[0];x+=2){
            ansx=(ansx+solx(x,m))%MOD;
        }
        for(int y=dw[1];y<=up[1];y+=2){
            ansy=(ansy+soly(y,m))%MOD;
        }
        cout<<ansx*ansy%MOD;
    }

}

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

signed main(){
    // freopen("wolf.in","r",stdin);
    // freopen("wolf.out","w",stdout);
    initpw();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>wx[i]>>wy[i];
    }
    Sub2::solve();
    return 0;
}