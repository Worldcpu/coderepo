#include<bits/stdc++.h>
using namespace std;
constexpr int MN=620,MOD=31011;
struct Edge{
    int u,v,w;
}e[MN],mst[MN];
int n,m,wtot,a[MN][MN],bel[MN],dtot,mtot,ans=1,dg[MN][MN],g[MN][MN];
bool visw[MN];
vector<Edge> ew[MN]; 

namespace HLS{

    int solve(int n){
        int ret=1,w=1;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                while(a[j][i]){
                    int div=a[i][i]/a[j][i];
                    for(int k=i;k<=n;k++){
                        a[i][k]=(a[i][k]-1ll*div*a[j][k]%MOD+MOD)%MOD;
                    }
                    swap(a[i],a[j]);
                    w=-w;
                }
            }
        }
        for(int i=1;i<=n;i++){
            ret=1ll*a[i][i]*ret%MOD;
        }
        ret=1ll*w*ret;
        return (ret+MOD)%MOD;
    }
}

namespace Kruskal{
    int pre[MN];

    void initpre(int n){
        for(int i=0;i<=n;i++) pre[i]=i;
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    void kru(){
        for(int i=1,lstw=0;i<=m;i++){
            if(e[i].w!=lstw){
                lstw=e[i].w;
                wtot++;
            }
            ew[wtot].push_back(e[i]);
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru!=rv){
                pre[ru]=rv;
                visw[wtot]=1;
                mst[++mtot]=e[i];
                mst[mtot].w=wtot;
            }
        }       
    }
}using namespace Kruskal;

bool cmp(Edge x,Edge y){
    return x.w<y.w;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    sort(e+1,e+1+m,cmp);
    initpre(n);
    kru();
    if(mtot!=n-1){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=wtot;i++){
        if(!visw[i]) continue;
        initpre(n);
        dtot=0;
        for(int j=1;j<=mtot;j++){
            if(mst[j].w==i) continue;
            pre[root(mst[j].u)]=root(mst[j].v);
        }
        for(int j=1;j<=n;j++){
            if(pre[j]==j) bel[j]=++dtot;
        }
        for(int j=1;j<=n;j++) bel[j]=bel[root(j)];
        for(auto p:ew[i]){
            int bu=bel[p.u],bv=bel[p.v];
            dg[bu][bu]++,dg[bv][bv]++;
            g[bu][bv]++,g[bv][bu]++;
        }
        for(int j=1;j<=dtot;j++){
            for(int k=1;k<=dtot;k++){
                a[j][k]=(dg[j][k]-g[j][k]+MOD)%MOD;
            }
        }
        ans=ans*HLS::solve(dtot-1)%MOD;
        for(auto p:ew[i]){
            int bu=bel[p.u],bv=bel[p.v];
            dg[bu][bu]--,dg[bv][bv]--;
            g[bu][bv]--,g[bv][bu]--;
        }       
    }   
    cout<<ans;
    return 0;
}