#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e4+15;
constexpr int KMAX=33;
int f[MN][16][KMAX],a[MN],n,q,g[KMAX],tmp[KMAX];

namespace ST{
    pir st[16][MN];
    void initst(){
        for(int i=1;i<=15;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }
    int queryst(int l,int r){
        int lg=__lg(r-l+1);
        return max(st[lg][l],st[lg][r-(1<<lg)+1]).second;
    }
}
using namespace ST;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        st[0][i]=pir(min(n,i+a[i]),i);
    }
    initst();
    for(int i=1;i<=n;i++)
        for(int j=0;j<KMAX;j++) // ← 修正: MN → KMAX
            f[i][0][j]=min(n,i+a[i]+j);

    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i<=n;i++)
            for(int k=0;k<KMAX;k++)          // ← 修正: MN → KMAX
                for(int x=0;x<=k;x++){
                    int ret=queryst(i,f[i][j-1][x]);
                    f[i][j][k]=max(f[i][j][k],f[ret][j-1][k-x]);
                }

    while(q--){
        int l,r,K,ans=0;
        cin>>l>>r>>K;
        if(l==r){cout<<0<<'\n';continue;}
        if(l+a[l]+K>=r){cout<<1<<'\n';continue;}
        for(int i=0;i<=K;i++) g[i]=l;

        for(int i=15;i>=0;i--){
            if((1<<i)>n) continue;
            for(int j=0;j<=K;j++) tmp[j]=g[j];                
            for(int j=0;j<=K;j++){
                int ret=queryst(l,g[j]);                      
                for(int k=0;j+k<=K;k++)
                    tmp[j+k]=max(tmp[j+k],f[ret][i][k]);      
            }
            bool flag=0;
            for(int j=0;j<=K;j++)
                if(tmp[j]>=r) flag=1;                        
            if(flag) continue;
            for(int j=0;j<=K;j++) g[j]=tmp[j];
            ans+=(1<<i);
        }
        cout<<ans+1<<'\n';                                      
    }
    return 0;
}
