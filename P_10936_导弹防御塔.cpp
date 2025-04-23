#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=50;
constexpr double eps=1e-9;
int n,m;
double t1,t2,v,l,r,dis[MN][MN],p[MN*MN];
pir atk[MN],pro[MN];
vector<int> adj[MN*MN];
bool vis[MN*MN];

double getdis(int x,int y){
    return sqrt((double)(atk[x].first-pro[y].first)*(atk[x].first-pro[y].first)+(atk[x].second-pro[y].second)*(atk[x].second-pro[y].second));
}

bool match(int u){
    for(auto v:adj[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!p[v]||match(p[v])){
                p[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

bool check(double mid){
    memset(p,0,sizeof(p));
    int num=min(m,(int)floor((mid+t2)/(t1+t2)));
    for(int i=1;i<=m;i++){
        adj[i].clear();
        for(int j=1;j<=n;j++){
            for(int k=1;k<=num;k++){
                if(dis[i][j]+t1*k+t2*(k-1)<=mid){
                    adj[i].push_back((j-1)*num+k);
                }
            }
        }
    }
    for(int i=1;i<=m;i++){
        memset(vis,0,sizeof(vis));
        if(!match(i)) return 0;
    }
    return 1;
}

int main(){
    cin>>n>>m>>t1>>t2>>v;
    t1/=60;
    for(int i=1;i<=m;i++){
        cin>>atk[i].first>>atk[i].second;
    }
    for(int i=1;i<=n;i++){
        cin>>pro[i].first>>pro[i].second;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            dis[i][j]=getdis(i,j)/v;
        }
    }
    l=0,r=10000;
    while(l+eps<r){
        double mid=(l+r)/2;
        if(check(mid)) r=mid;
        else l=mid;
    }
    cout<<fixed<<setprecision(6)<<r;
    return 0;
}