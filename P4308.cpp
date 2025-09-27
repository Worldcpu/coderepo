#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
constexpr double eps=1e-10;
int n,m,st;
double w[MN],p,ans;
double dis[MN][MN],tmpdis[MN][MN];
bool mp[MN][MN],tmpmp[MN][MN];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    cin>>st>>p;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        dis[u][v]+=w[v]*p;
        mp[u][v]=1;
    }
    
    while(p>eps){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                tmpdis[i][j]=dis[i][j];
                tmpmp[i][j]=mp[i][j];
            }
        }
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(tmpmp[i][k]&&tmpmp[k][j]) dis[i][j]=max(dis[i][j],tmpdis[i][k]+tmpdis[k][j]*p);
                    mp[i][j]|=(tmpmp[i][k]&&tmpmp[k][j]);
                }
            }
        }
        p*=p;
    }
    for(int i=1;i<=n;i++){
        ans=max(ans,dis[st][i]);
    }
    cout<<fixed<<setprecision(12)<<ans+w[st];
    cerr<<sizeof(double);

    return 0;
}