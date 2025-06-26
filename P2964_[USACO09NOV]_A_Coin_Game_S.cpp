#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e3+1;
int f[MN][MN],n,s[MN],c[MN];

int dfs(int x,int y){
    y=min(y,n-x+1);
    if(~f[x][y]) return f[x][y];
    if(x+y>n) return s[x];
    if(!y) return 0;
    int ans=dfs(x,y-1);
    ans=max(ans,s[x]-dfs(x+y,y<<1));
    return f[x][y]=ans;
}

signed main(){
    cin>>n;
    memset(f,-1,sizeof(f));
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=n;i>=1;i--) s[i]=s[i+1]+c[i];
    cout<<dfs(1,2);
    return 0;
}
