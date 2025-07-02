#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=15,INF=1e18;
int a[MN][MN],b[MN][MN],c[MN],ed,n,m;
map<int,int> ans,vis;

int dfs(int x,int y){
    if(x==ed) return 0;
    if(vis[x]==1) return ans[x];
    vis[x]=1;
    int p=1,sum=y?INF:-INF,tmp=x;
    c[0]=INF;
    for(int i=1;i<=n;i++) c[i]=tmp%11,tmp/=11;
    if(y){
        for(int i=1;i<=n;i++){
            if(c[i]<min(c[i-1],m)) sum=min(sum,dfs(x+p,y^1)-b[i][c[i]+1]);
            p*=11;
        }
    }
    else {
        for(int i=1;i<=n;i++){
            if(c[i]<min(c[i-1],m)) sum=max(sum,dfs(x+p,y^1)+a[i][c[i]+1]);
            p*=11;
        }
    }
    ans[x]=sum;
    return ans[x];
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>b[i][j];
        }
    }
    for(int i=1;i<=n;i++) ed=ed*11+m;
    cout<<dfs(0,0);
    return 0;
}
