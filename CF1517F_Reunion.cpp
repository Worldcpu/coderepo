#include<bits/stdc++.h>
#define pir pair<int,int>
#define int long long
using namespace std;
constexpr int MN=520,MR=300,MOD=998244353,INV=(MOD+1)/2;
int f[MN][MN<<1],ans,r,n,m;
vector<int> adj[MN];

void mergef(int x,int y){
    vector<pir> vx,vy;
    for(int i=0;i<=2*MR;i++){
        if(f[x][i]){
            vx.push_back(pir(i-MR,f[x][i]));
            f[x][i]=0;
        }
        if(f[y][i]){
            vy.push_back(pir(i-MR,f[y][i]));
        }
    }
    for(auto p:vx){
        for(auto q:vy){
            int val=p.second*q.second%MOD;
            if(p.first<0&&q.first<0){
                (f[x][min(p.first,q.first-1)+MR]+=val)%=MOD;
            }
            if(p.first>=0&&q.first<0){
                (f[x][(p.first+q.first>=0?p.first:q.first-1)+MR]+=val)%=MOD;
            }
            if(p.first<0&&q.first>=0){
                (f[x][(p.first+q.first>=0?q.first-1:p.first)+MR]+=val)%=MOD;
            }
            if(p.first>=0&&q.first>=0){
                (f[x][max(p.first,q.first-1)+MR]+=val)%=MOD;
            }
        }
    }
}

void dfs(int u,int pre){
    f[u][r+MR]=f[u][MR-1]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        mergef(u,v);
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(r=1;r<=n;r++){
        memset(f,0,sizeof(f));
        dfs(1,0);
        for(int i=0;i<MR;i++){
            (ans+=f[1][i])%=MOD;
        }
    }
    ans=(ans-1+MOD)%MOD;
    for(int i=1;i<=n;i++){
        ans=ans*INV%MOD;
    }
    cout<<ans;

    return 0;
}
