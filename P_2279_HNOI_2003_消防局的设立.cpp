#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int MN=1500;
int n,dp[MN][5];
vector<int> adj[MN];
void dfs(int u){
    dp[u][4]=1;
    for(auto v:adj[u]){
        dfs(v);
        dp[u][4]+=dp[v][0];
        dp[u][1]+=dp[v][2];
        dp[u][0]+=dp[v][1];
    }
    if(adj[u].empty()){
        dp[u][2]=dp[u][3]=1;
    }else{
        dp[u][2]=dp[u][3]=1e9;
        int cnt1=0,cnt2=0;
        for(auto v:adj[u]){
            cnt1+=dp[v][1];
            cnt2+=dp[v][2];
        }
        for(auto v:adj[u]){
            dp[u][3]=min(cnt1-dp[v][1]+dp[v][4],dp[u][3]);
            dp[u][2]=min(cnt2-dp[v][2]+dp[v][3],dp[u][2]);
        }
    }
    for(int i=3;i>=0;i--){
        dp[u][i]=min(dp[u][i+1],dp[u][i]);
    }
}
int main(){
    cin>>n;
    for(int i=2;i<=n;i++){
        int k;
        cin>>k;
        adj[k].push_back(i);
    }
    dfs(1);
    cout<<dp[1][2];
    return 0;
}