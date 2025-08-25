#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=20,MS=1<<20;
int f[MS],g[MS],n,m,ans=1;
bool vis[MN][MN],q[MS];

bool cmp(int s,int x,int y){
    return ((s>>x)&1)>((s>>y)&1);
}

signed main(){
    cin>>n>>m;
    for(int i=0;i<1<<n;i++) f[i]=i;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            vis[i][j]=1;
        }
    }
    for(int i=0;i<=n;i++){
        q[((1<<i)-1)<<(n-i)]=1;
    }
    while(m--){
        int a,b;
        cin>>a>>b;
        a=(a+ans)%n,b=(b+ans*2)%n;
        if(a>b) swap(a,b);
        if(!vis[a][b]){
            cout<<ans<<'\n';
            continue;
        }
        for(int i=0;i<n;i++){
            vis[a][i]=vis[b][i]=vis[i][a]=vis[i][b]=0;
        }
        for(int i=0;i<(1<<n);i++){
            if(cmp(f[i],a,b)){
                f[i]^=(1<<a)|(1<<b);
            }
            for(int j=0;j<n;j++){
                if(j<a) vis[j][a]|=cmp(f[i],j,a);
                else vis[a][j]|=cmp(f[i],a,j);
                if(j<b) vis[j][b]|=cmp(f[i],j,b);
                else vis[b][j]|=cmp(f[i],b,j);
            }
        }
        memset(g,0,sizeof(g));
        g[0]=1;
        for(int i=1;i<1<<n;i++){
            if(q[f[i]]){
                for(int j=0;j<n;j++){
                    if(i&(1<<j)) g[i]+=g[i^(1<<j)];
                }
            }
        }
        cout<<(ans=g[(1<<n)-1])<<'\n';
    }

    return 0;
}