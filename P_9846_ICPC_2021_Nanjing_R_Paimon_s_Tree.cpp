#include <bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN = 250;
struct Node{
    int u,fa,dis;
};
int n,m,a[MN],pth[MN],dep[MN],lst[MN],siz[MN],sum[MN];
long long f[MN][MN][MN];
vector<int> adj[MN];
bool vis[MN];

template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

pir bfs(int s){
    pir ans=pir(-1,s);
    queue<Node> q;
    lst[s]=lst[0]=0;
    q.push({s,0,0});
    while(!q.empty()){
        auto f=q.front();
        q.pop();
        ans=max(ans,pir(f.dis,f.u));
        lst[f.u]=f.fa;
        for(auto v:adj[f.u]){
            if(v==f.fa) continue;
            q.push({v,f.u,f.dis+1});
        }
    }
    return ans;
}

void getsiz(int u,int fa){
    siz[u]=1;
    for(auto v:adj[u]){
        if(v==fa||vis[v]) continue;
        getsiz(v,u);
        siz[u]+=siz[v];
    }
}

void init(){
    memset(f,0,sizeof(f));
    for(int i=1;i<=n+1;i++){
        a[i]=pth[i]=siz[i]=dep[i]=sum[i]=lst[i]=0;
        adj[i].clear();
        vis[i]=0;
    }
    m=0;
}

void solve()
{
    read(n);
    init();
    for (int i = 1; i <= n; i++)
    {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        read(u);
        read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pir dim=bfs(bfs(1).second);
    for(int i=dim.second;i;i=lst[i]){
        pth[++m]=i;
        vis[i]=1;
        // cout<<i<<" ";
    }
    for(int i=1;i<=m;i++){
        getsiz(pth[i],0);
        sum[i]=sum[i-1]+siz[pth[i]];
    }

    for(int len=1;len<=m;len++){
        for(int l=1,r;l+len-1<=m;l++){
            r=l+len-1;
            for(int t=len;t<sum[r]-sum[l-1];t++){
                f[l][r][t]=max(f[l][r][t],f[l][r][t-1]);
            }
            for(int t=len-1;t<sum[r]-sum[l-1];t++){
                if(l>1){
                    f[l-1][r][t+1]=max(f[l-1][r][t+1],f[l][r][t]+a[t+1]);
                }
                if(r<m){
                    f[l][r+1][t+1]=max(f[l][r+1][t+1],f[l][r][t]+a[t+1]);
                }
            }
        }
    }
    cout<<f[1][m][n]<<'\n';

    // for (int i = 1; i <= k; i++)
    // {
    //     ret += a[i];
    // }
    // cout << ret;
}

signed main(){
    ios::sync_with_stdio(0);
    int T;
    read(T);
    while(T--){
        // cout<<"AWA";
        solve();
    }
}