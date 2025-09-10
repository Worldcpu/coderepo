#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=620;
int n,m,a[MN][MN];

namespace HLS{

    int solve(){
        int ret=1,w=1;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                while(a[i][i]){
                    int div=a[j][i]/a[i][i];
                    for(int k=i;k<=n;k++){
                        a[j][k]=(a[j][k]-1ll*div*a[i][k]);
                    }
                    swap(a[i],a[j]);
                    w=-w;
                }
                swap(a[i],a[j]);
                w=-w;
            }
        }
        for(int i=1;i<=n;i++){
            ret=1ll*a[i][i]*ret;
        }
        ret=1ll*w*ret;
        return ret;
    }

}

void init(){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            a[i][j]=0;
        }
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        a[u][u]++;
        a[v][v]++;
        a[u][v]--;
        a[v][u]--;
    }
    n--;
    cout<<HLS::solve()<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}