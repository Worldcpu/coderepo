#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e6+15,MM=2e5+15,MOD=998244353;
int pw[MN],inv[MN],n,m,b0,ppm[MN],ppm1[MN];

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

namespace SUB1{ //dp
    constexpr int MQ=3520;
    int f[2][MQ],ret;
    // f[MN][MQ]，MLE On Test case 1 boom boom boom!

    void init(){
        ret=0;
        for(int i=0;i<=m;i++){
            f[0][i]=0;
        }
    }

    void initdp(int f[]){
        for(int i=0;i<=m;i++) f[i]=0;
    }

    int solve(){
        init();
        f[0][b0]=1;
        int now=0,nxt=1;
        for(int i=0;i<n;i++,nxt^=1,now^=1){
            initdp(f[nxt]);
            for(int j=0;j<m;j++){
                if(!f[now][j]) continue;
                if(j){
                    f[nxt][j-1]=(f[nxt][j-1]+f[now][j])%MOD;
                }
                if(j+1<m){
                    f[nxt][j+1]=(f[nxt][j+1]+f[now][j])%MOD;
                }else ret=(ret+f[now][j]%MOD*(m-1)%MOD*ppm[n-i-1]%MOD*ppm1[(i+j-b0)/2]%MOD)%MOD;//这里应该时 ppm[n-i] ppm1[(i+j-b0-1)]，但是因为 i 从 0 开始枚举的搞笑了
            }
        }
        for(int i=0;i<m;i++){
            if(f[now][i]){
                ret=(ret+f[now][i]*ppm1[(i+n-b0)/2]%MOD)%MOD;// 同理
            }
        }
        return ret;
    }

}

namespace SUB2{ // rong chi

    void flip(pir &x,int k){
        swap(x.first,x.second);
        x.first-=k;
        x.second+=k;
    }

    int calc(pir x){
        if(x.first<0||x.second<0) return 0;
        return getC(x.first+x.second,x.first);
    }

    int sol(int x,int y,int fl,int fr){ 
        // from (0,0) to (x,y),y must in [fl,fr]
        // maybe fl>fr,But this is reflective inclusion-exclusion,I don't care ¯\_(ツ)_/¯
        pir pos=pir(x,y);
        int ret=calc(pos);
        while(pos.first>=0&&pos.second>=0){
            flip(pos,fl);
            ret=(ret-calc(pos)+MOD)%MOD;
            flip(pos,fr);
            ret=(ret+calc(pos))%MOD;
        }
        pos=pir(x,y);
        while(pos.first>=0&&pos.second>=0){
            flip(pos,fr);
            ret=(ret-calc(pos)+MOD)%MOD;
            flip(pos,fl);
            ret=(ret+calc(pos))%MOD;
        }
        return ret;
    }

    int solve(){
        int x=b0,y=0,ret=ksm(m,n);
        for(int i=b0;i<n;i+=2,x++,y++){
            ret=(ret-sol(x,y,m-b0,-1-b0)*ppm[n-i-1]%MOD*ppm1[y]%MOD+MOD)%MOD;
        }
        return ret;
    }

}

void init(){
    ppm[0]=ppm1[0]=1;
    for(int i=1;i<=n;i++){
        ppm[i]=ppm[i-1]*m%MOD;
        ppm1[i]=ppm1[i-1]*(m-1)%MOD;
    }
}

void solve(){
    cin>>n>>m>>b0;
    if(b0>=m){
        cout<<ksm(m,n)<<'\n';
        return;
    }
    init();
    if(m*m<=n){
        cout<<SUB1::solve()<<'\n';
    }else cout<<SUB2::solve()<<'\n';
}

signed main(){
    initpw();
    int T;
    cin>>T;
    while(T--){
        solve();
    }


    return 0;
}