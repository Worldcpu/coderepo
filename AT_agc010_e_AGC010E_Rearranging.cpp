#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=2520;
int n,a[MN];
bool mp[MN][MN],vis[MN];
priority_queue<int> q;
vector<int> adj[MN],ans;

void dfs(int u){
    vis[u]=1;
    for(int v=1;v<=n;v++){
        if(!vis[v]&&mp[u][v]){
            adj[u].push_back(v);
            dfs(v);
        }
    }
}

void topo(){
    while(!q.empty()){
        int u=q.top();
        q.pop();
        ans.push_back(u);
        for(auto v:adj[u]){
            q.push(v);
        }
    }
}


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            mp[i][j]=mp[j][i]=(__gcd(a[i],a[j])>1);
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            q.push(i);
            dfs(i);
        }
    }
    topo();
    for(auto qwq:ans) cout<<a[qwq]<<" ";
    return 0;
}
