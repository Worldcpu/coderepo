#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=520;
int n,m,tot;
pir pr[MN];
bool vis[MN];

double dis(pir x,pir y){
    return sqrt(1.0*(x.first-y.first)*(x.first-y.first)+1.0*(x.second-y.second)*(x.second-y.second));
}

signed main(){
    freopen("bus.in","r",stdin);
    freopen("bus.out","w",stdout);
    cin>>n>>m;
    while(m--){
        int op,p;
        cin>>op;
        if(op==1){
            double mx=-1;
            pir pos=pir(1,1);
            for(int i=1;i<=n;i++){
                for(int j=1;j<=2;j++){
                    double minn=1e9;
                    for(int k=1;k<=tot;k++){
                        if(vis[k]) continue;
                        minn=min(minn,dis(pir(i,j),pr[k]));
                    }
                    if(mx<minn){
                        mx=minn;
                        pos=pir(i,j);
                    }
                }
            }
            pr[++tot]=pos;
            cout<<pos.first<<" "<<pos.second<<'\n';
        }else{
            int qwq;
            cin>>qwq;
            vis[qwq]=1;
        }
    }

    return 0;
}