#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55;
struct Op{
    int x,y,z;
};
int n,MOD,matx[MN][MN],maty[MN][MN],suma,H[MN],L[MN],Hb[MN],Lb[MN],sumb;
int matA[MN][MN],ret[MN][MN];
vector<Op> op;

int ksm(int a,int b){
    int ret=1;
    while(b>0){
        if(b&1) ret=ret*a%MOD;
        a=a* a %MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            matx[i][j]=maty[i][j]=matA[i][j]=ret[i][j]=0;
        }
        H[i]=L[i]=Hb[i]=Lb[i]=0;
    }
    suma=sumb=0;
    op.clear();
}

void solve(){
    cin>>n>>MOD;
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>matx[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>maty[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            matA[i][j]=(maty[i][j]-matx[i][j]+MOD)%MOD;
            suma=(suma+matA[i][j])%MOD;
            H[i]=(H[i]+matA[i][j])%MOD;
            L[j]=(L[j]+matA[i][j])%MOD;
        }
    }

    if((2*n-1)%MOD==0&&suma%MOD!=0){
        cout<<"No\n";
        return;
    }
    if((2*n-1)%MOD!=0){
        sumb=suma*ksm(2*n-1,MOD-2)%MOD;
    }else sumb=0;

    if((n-1)%MOD!=0){
        for(int i=1;i<=n;i++){
            Hb[i]=(H[i]-sumb+MOD)%MOD*ksm(n-1,MOD-2)%MOD;
            Lb[i]=(L[i]-sumb+MOD)%MOD*ksm(n-1,MOD-2)%MOD;
        }
    }else{
        for(int i=2;i<=n;i++){
            if(H[i]!=H[1]||L[i]!=L[1]){
                cout<<"No\n";
                return;
            }
        }
        Hb[1]=H[1]%MOD;
        Lb[1]=L[1]%MOD;
        for(int i=2;i<=n;i++) Hb[i]=Lb[i]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ret[i][j]=(Hb[i]+Lb[j]-matA[i][j]+MOD)%MOD;
        }
    }
    cout<<"Yes\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(ret[i][j]>0){
                op.push_back({i,j,ret[i][j]});
            }
        }
    }
    cout<<op.size()<<'\n';
    for(auto p:op){
        cout<<p.x<<' '<<p.y<<' '<<p.z<<'\n';
    }
}

signed main(){
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
