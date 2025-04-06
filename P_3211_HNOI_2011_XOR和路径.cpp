#include<bits/stdc++.h>
using namespace std;
const int MN=1000+15;
const double eps=1e-8;
struct edge{
    int v,w;
};
int n,m,dg[MN];
double mat[MN][MN],ans=0;
vector<edge> adj[MN];

bool gauss(){
    for(int i=1;i<=n;i++){
        //找到第i列第一个非0
        for(int j=i;j<=n;j++){
            if(fabs(mat[j][i])>eps){
                //如果非0
                swap(mat[j],mat[i]);//交换行
                break;
            }
        }
        if(fabs(mat[i][i])<eps){
            return 0;
        }
        for(int j=n+1;j>=i;j--){
            mat[i][j]/=mat[i][i];
        }
        for(int j=i+1;j<=n;j++){
            for(int k=n+1;k>=i;k--){
                mat[j][k]-=mat[j][i]*mat[i][k];
            }
        }
    }
    for(int i=n-1;i>=1;i--){
        for(int j=i+1;j<=n;j++){
            mat[i][n+1]-=mat[i][j]*mat[j][n+1];
        }
    }
    return 1;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(u==v){
            adj[u].push_back({v,w});
            dg[u]++;
        }else{
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
            dg[u]++;
            dg[v]++;
        }
    }
    for(int i=30;i>=0;i--){
        memset(mat,0,sizeof(mat));
        for(int j=1;j<n;j++){
            mat[j][j]=-dg[j];
            for(auto e:adj[j]){
                int v=e.v,w=(e.w>>i)&1;
                if(w){
                    mat[j][v]-=1;
                    mat[j][n+1]-=1;
                }else mat[j][v]+=1;
            }
        }
        mat[n][n]=1;
        gauss();
        ans+=(1<<i)*mat[1][n+1];
    }
    
    cout<<fixed<<setprecision(3)<<ans;
    return 0;
}