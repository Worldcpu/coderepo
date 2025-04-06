#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int MN=2000;
int n,dp[MN][2];
vector<int> adj[MN];
void dfs(int u,int fa){
    dp[u][1]=1;
    dp[u][0]=0;
    for(auto v:adj[u]){
        if(v!=fa){
            dfs(v,u);
            dp[u][0]+=dp[v][1];
            dp[u][1]+=min(dp[v][0],dp[v][1]);
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int c,k;
        cin>>c>>k;
        for(int j=1;j<=k;j++){
            int v;
            cin>>v;
            adj[c].push_back(v);
            adj[v].push_back(c);
        }
    }
    dfs(0,-1);
    cout<<min(dp[0][0],dp[0][1]);
    return 0;
}