#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,MD=25;
int f[2][MD][MN],n,m,d,L[MN],q[MN],ql,qr,mx[MN],qm;
pir a[MN];

void init(){
    for(int i=0;i<2;i++)
        for(int j=0;j<MD;j++)
            for(int k=1;k<=m;k++)
                f[i][j][k]=-1;
    ql=qr=0;
}

void solve(){
    cin>>n>>m>>d;
    init();
    for(int i=1;i<=n;i++){
        cin>>L[i];
    }
    for(int i=1;i<=m;i++){
        cin>>a[i].first>>a[i].second;
        if(a[i].second==2) a[i].second=0;
    }
    sort(L+1,L+1+n);
    sort(a+1,a+1+m);
    n<<=1;
    int now=0,lst=1;

    for(int i=1;i<=m;i++){
        if(a[i].first<=L[1]){
            f[0][a[i].second][i]=a[i].first;
        }
    }
    for(int i=2;i<=n;i++){
        now^=1,lst^=1;
        for(int j=0;j<=n;j++)
            for(int k=0;k<=m;k++)
                f[now][j][k]=-1;
        if(i&1){ 
            for(int j=0;j<=n;j++){
                int premx=-1;
                for(int k=1;k<=m;k++){
                    if(premx!=-1){
                        f[now][j+a[k].second][k]=max(f[now][j+a[k].second][k],premx+a[k].first);
                    }
                    premx=max(premx,f[lst][j][k]);
                }
            }
        }else{ 
            for(int j=0;j<=n;j++){
                for(int k=1;k<=m;k++) mx[k]=-1;
                ql=1,qr=-1,qm=0;
                for(int k=1;k<=m;k++){
                    if(a[k].first>L[i>>1]) break;
                    while(ql<k&&(a[k].first-a[ql].first)>d){
                        ql++;
                        if(ql>qm){
                            qr=-1;
                            qm=k-1;
                            for(int t=qm;t>=ql;t--){
                                mx[t]=max(mx[t+1],f[lst][j][t]);
                            }
                        }
                    }
                    if(max(qr,mx[ql])!=-1){
                        f[now][j+a[k].second][k]=max(f[now][j+a[k].second][k],max(qr,mx[ql])+a[k].first); // 修正加分
                    }
                    qr=max(qr,f[lst][j][k]);
                }
            }
        }
    }
    for(int i=0;i<=n;i++){
        int ret=-1;
        for(int j=1;j<=m;j++)
            ret=max(ret,f[now][i][j]);
        cout<<ret<<' ';
    }
    cout<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
