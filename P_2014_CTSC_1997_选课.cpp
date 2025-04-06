#include<iostream>
#include<vector>
using namespace std;
const int MN=350;
vector<int> adj[MN];
int n,m,score[MN],dp[MN][MN];
void dfs(int u){
    for(auto v:adj[u]){
        dfs(v);
        for(int i=m+1;i>=1;i--){
            for(int j=0;j<i;j++){
                dp[u][i]=max(dp[u][i],dp[u][i-j]+dp[v][j]);
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k>>score[i];
        dp[i][1]=score[i];
        adj[k].push_back(i);
    }
    dfs(0);
    cout<<dp[0][m+1];
    return 0;
}