#include<bits/stdc++.h>
using namespace std;
constexpr int MN=55;
int n,siz[MN];
double pw[MN],C[MN][MN],f[MN][MN],g[MN],tmp[MN];
vector<int> adj[MN];

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i;
    for(int i=0;i<MN;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
}

void dfs(int u,int pre){
    siz[u]=1;
    f[u][0]=1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        memset(g,0,sizeof(g));
        for(int i=0;i<=siz[v];i++){
            for(int j=1;j<=siz[v];j++){
                if(j<=i) g[i]+=f[v][j-1]/2;
                else g[i]+=f[v][i];
            }
        }
        for(int i=0;i<siz[u];i++){
            for(int j=0;j<=siz[v];j++){
                tmp[i+j]+=f[u][i]*g[j]*C[i+j][i]*C[siz[u]-i-1+siz[v]-j][siz[v]-j];
            }
        }
        siz[u]+=siz[v];
        for(int i=0;i<siz[u];i++){
            f[u][i]=tmp[i];
            tmp[i]=0;
        }
    }
}

int main(){
    initpw();
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        memset(f,0,sizeof(f));
        memset(siz,0,sizeof(siz));
        dfs(i,0);
        cout<<fixed<<setprecision(10)<<f[i][n-1]/pw[n-1]<<'\n';
    }

    return 0;
}