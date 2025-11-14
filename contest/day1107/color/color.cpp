#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],b[MN],in[MN],cnt0,cnt1,ans;
bool vis[MN],visnum[MN];
vector<int> adj[MN];

void dfs(int u){
    vis[u]=1;
    cnt1+=(in[u]>0);
    cnt0+=(in[u]==0); 
    for(auto v:adj[u]){
        if(vis[v]) continue;
        dfs(v);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        if(a[i]==b[i]){
            visnum[a[i]]=1;
            continue;
        }
        adj[a[i]].push_back(b[i]);
        adj[b[i]].push_back(a[i]);
        in[b[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(visnum[i]) continue;
        if(!vis[i]){
            cnt0=cnt1=0;
            dfs(i);
            if(cnt0>=2){
                cout<<-1;
                return 0;
            }
            ans+=cnt1+cnt0+1;
        }
    }
    cout<<ans;
    return 0;
}