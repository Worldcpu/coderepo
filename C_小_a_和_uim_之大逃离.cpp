// #include<iostream>
// #include<cstring>
// using namespace std;
// const int MOD=1000000007;
// int n,m,w;
// int dp[850][850][20][2];
// int map[850][850];
// int main(){
//     memset(dp,-1,sizeof(dp));
//     cin>>n>>m>>w;
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=m;j++){
//             cin>>map[i][j];
//         }
//     }
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=m;j++){
//             for(int k=w;k>=map[i][j];k--){
//                 dp[i][j][k][0]=dp[i][j][k][1]=0;
//                 dp[i][j][k][0]+=dp[i-1][j][k-map[i][j]][1]+dp[i][j-1][k-map[i][j]][1]+2;
//                 dp[i][j][k][1]+=dp[i-1][j][k-map[i][j]][0]+dp[i][j-1][k-map[i][j]][0]+2;
//             }
//         }
//     }
//     int ans=-1;
//     for(int k=1;k<=w;k++){
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=m;j++){
//             cout<<dp[i][j][k][1]<<" ";
//         }
//         cout<<endl;
//     }
//     cout<<endl;
//     }
//     return 0;
// }
#include<iostream>
using namespace std;
int MOD;
int n,m,k,map[850][850],f[2];
long long ans=0;
// void dfs(int i,int j,int ap,int up,int p){
//     if(i<1||i>n||j<1||j>m||ap>k||up>k) return;
//     if(p==1&&ap==up+map[i][j]&&up+map[i][j]<=k){
//         ans++;
//         cout<<i<<" "<<j<<endl;
//         return;
//     }
//     if(p==0&&ap+map[i][j]<=k){
//         dfs(i+1,j,ap+map[i][j],up,1);
//         dfs(i,j+1,ap+map[i][j],up,1);
//     }
//     if(p==1&&up+map[i][j]<=k){
//         dfs(i+1,j,ap,up+map[i][j],0);
//         dfs(i,j+1,ap,up+map[i][j],0);
//     }
// }
void dfs(int i,int j,int ap,int up,int p){
    if(i<1||i>n||j<1||j>m||ap>k||up>k) return;
    
    if(p==0){
        ap=(ap+map[i][j])%MOD;
    }else up=(up+map[i][j])%MOD;
    // cout<<"NOW "<<i<<" "<<j<<" "<<f[0]<<" "<<f[1]<<endl;
    if(ap>k||up>k){ return;}
    if(p==1&&ap==up){
        ans++;
        // cout<<"ANS:"<<i<<" "<<j<<endl;
    }
    dfs(i+1,j,ap,up,p^1);
    dfs(i,j+1,ap,up,p^1);
}
int main(){
    cin>>n>>m>>k;
    MOD=k+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>map[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            // cout<<"NEWONE"<<endl;
            f[0]=f[1]=0;
            dfs(i,j,0,0,0);
        }
    }
    cout<<ans;
    return 0;
}