#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
constexpr int MN=5e5+15;
int n,x[MN],y[MN],col[MN];
vector<int> adj[MN];
gp_hash_table<int,int> mpx,mpy;

void dfs(int u){
    for(auto v:adj[u]){
        if(~col[v]) continue;
        col[v]=col[u]^1;
        dfs(v);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        if(!mpx[x]){
            mpx[x]=i;
        }else{
            adj[mpx[x]].push_back(i);
            adj[i].push_back(mpx[x]);
            mpx[x]=0;
        }
        if(!mpy[y]){
            mpy[y]=i;
        }else{
            adj[mpy[y]].push_back(i);
            adj[i].push_back(mpy[y]);
            mpy[y]=0;
        }
    }
    memset(col,-1,sizeof(col));
    for(int i=1;i<=n;i++){
        if(col[i]==-1){
            col[i]=0;
            dfs(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]==0){
            cout<<'b';
        }else cout<<'r';
    }

    return 0;
}