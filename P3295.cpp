#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int ML=30,MN=1e5+15,MOD=1e9+7;
int n,m,ans;
pir qj[2][MN];

namespace DSU{
    int pre[ML+2][MN];

    void initpre(){
        for(int i=0;i<=ML;i++){
            iota(pre[i]+1,pre[i]+1+n,1);
        }
    }

    int root(int x,int pre[]){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x],pre);
    }

    void merge(int x,int y,int pre[]){
        int rx=root(x,pre),ry=root(y,pre);
        if(rx==ry) return;
        pre[rx]=ry;
    }
}using namespace DSU;

signed main(){
    cin>>n>>m;
    initpre();
    for(int i=1;i<=m;i++){
        for(int j=0;j<2;j++){
            cin>>qj[j][i].first>>qj[j][i].second;
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=ML;j>=0;j--){
            if(qj[0][i].first+(1<<j)-1<=qj[0][i].second){
                merge(qj[0][i].first,qj[1][i].first,pre[j]);
                qj[0][i].first+=1<<j;
                qj[1][i].first+=1<<j;
            }
        }
    }
    for(int i=ML;i>=1;i--){
        for(int j=1;j+(1<<i)-1<=n;j++){
            int pos=root(j,pre[i]);
            merge(j,pos,pre[i-1]);
            merge(j+(1<<i-1),pos+(1<<i-1),pre[i-1]);
        }
    }
    for(int i=1;i<=n;i++){
        if(pre[0][i]==i){
            ans=(ans==0?9:ans*10%MOD);
        }
    }
    cout<<ans;
    return 0;
}