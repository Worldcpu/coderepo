#include<bits/stdc++.h>
#define pir pair<int,int>
#define int long long
using namespace std;
constexpr int MN=5520,ML=600,INF=1e18;
struct Node{
    int c,d;
}a[MN];
int f[MN][MN],g[MN],n,h,ans=INF;
vector<pir> qwq;

bool cmp(Node x,Node y){
    return x.c<y.c;
}

bool cmpp(pir x,pir y){
    if(x.second/x.first==y.second/y.first){
        return x.second<y.second;
    }
    return x.second/x.first>y.second/y.first;
}

signed main(){
    cin>>n>>h;
    for(int i=1;i<=n;i++){
        cin>>a[i].c>>a[i].d;
        a[i].c*=-1;
    }
    sort(a+1,a+1+n,cmp);
    memset(f,128,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=ML;i++){
        for(int j=0;j<=ML;j++){
            for(int k=1;k<=n;k++){
                if(j-a[k].c>ML||j-a[k].c<0) continue;
                f[i][j]=max(f[i][j],f[i-1][j-a[k].c]+a[k].d);
            }
        }
    }
    for(int i=1;i<=ML;i++){
        int ret=0;
        for(int j=0;j<=ML;j++){
            ret=max(ret,f[i][j]);
        }
        qwq.push_back({i,ret});
    }
    sort(qwq.begin(),qwq.end(),cmpp);
    for(auto p:qwq){
        for(int i=p.first;i<=ML*ML;i++){
            g[i]=max(g[i],g[i-p.first]+p.second);
        }
    }
    for(int i=0;i<=ML*ML;i++){
        int t=h-g[i],v=(t+qwq[0].second-1)/qwq[0].second;
        v=max(0ll,v);
        ans=min(ans,i+v*qwq[0].first);
    }
    cout<<ans;
    return 0;
}