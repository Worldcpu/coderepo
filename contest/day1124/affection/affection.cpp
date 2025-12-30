#include<bits/stdc++.h>
using namespace std;
constexpr int MN=420,INF=1e9+7;
int n,m,a[MN],f[MN][2],b[2],dw,up,ans;

int dodp(){
    for(int i=0;i<=n;i++){
        f[i][0]=f[i][1]=INF;
    }

    f[1][0]=(b[0]-a[1]<0?INF:b[0]-a[1]);
    if(m==2){
        f[1][1]=(b[1]-a[1]<0?INF:b[1]-a[1]);
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<m;j++){
            if(b[j]-a[i]<0) continue;
            for(int k=0;k<m;k++){
                f[i][j]=min(f[i][j],f[i-1][k]+max(b[j]-a[i]-b[k]+a[i-1],0));
            }
        }
    }
    return min(f[n][0],f[n][1]);
}

void init(){
    ans=INF;    
    for(int i=0;i<=n;i++){
        f[i][0]=f[i][1]=INF;
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    dw=*min_element(a+1,a+1+n);
    up=*max_element(a+1,a+1+n);
    for(int b0=dw;b0<=up;b0++){
        for(int b1=b0;b1<=up+50;b1++){
            b[0]=b0,b[1]=b1;
            ans=min(ans,dodp());
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}

// 2e8？
// 今天又是大家喜闻乐见的 S2OJ。
// 对面橘猫猫放了一个防快车里把我的皮猫猫在 T1 就给狙了，原来我不会子区间问题啊。那 NOIP 2024 T4 又是怎么一回事呢？这下不得不加训了。
// T2 随便设一个 dp 就没了，但是没发现枚举上界还要开大一点。
// T3 怎么又是子区间问题。
// 但是比赛快结束了，发现我连个大样例都没有。
// 开网下下来但是 7-zip 都打不开，我一看欧呦原来是大样例只有 3KB 啊那我剩下的数据都去哪里了呢？
// 受不了直接投翔。

