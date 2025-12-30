#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,q,zd,lstans,testmode,val[MN];
vector<int> adj[MN];

void dfs(int u,int pre,int w,int cnt){
    if(u==zd){
        cnt+=(w>=val[u]);
        lstans=cnt;
        cout<<cnt<<'\n';
        return;
    }
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u,w+val[u],cnt+(w>=val[u]));
    }
}

int main(){
    cin>>testmode>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    while(q--){
        int op,x,y;
        cin>>op>>x>>y;
        x=x^(lstans*testmode);
        y=y^(lstans*testmode);
        if(op==0){
            adj[x].push_back(y);
            adj[y].push_back(x);
        }else{
            zd=y;
            dfs(x,0,0,0);
        }
    }

    return 0;
}