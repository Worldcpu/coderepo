#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=1e9+7;
struct Edge{
    int u,v,w;
}e[MN];
int n,m,x,e1,e2,ppm;
bool vise[MN];

namespace Kruskal{
    int pre[MN];

    void initpre(){
        for(int i=1;i<=n;i++) pre[i]=i;
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    int kruskal(){
        int ret=0;
        for(int i=1;i<=m;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru!=rv){
                pre[ru]=rv;
                ret+=e[i].w;
            }
        }
        return ret;
    }
}using namespace Kruskal;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

bool cmp(Edge x,Edge y){
    return x.w<y.w;
}

signed main(){
    cin>>n>>m>>x;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    sort(e+1,e+1+m,cmp);
    initpre();
    ppm=kruskal();
    if(ppm>x){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=m;i++){
        initpre();
        pre[e[i].u]=pre[e[i].v];
        int ret=kruskal()+e[i].w;
        if(ret==x) e1++;
        else if(ret>x) e2++;
        vise[i]=0;
    }
    if(ppm==x){
        cout<<ksm(2,e2)*(ksm(2,e1)-2+MOD)%MOD;
    }else{
        cout<<ksm(2,e2+1)*(ksm(2,e1)-1+MOD)%MOD;
    }

    return 0;
}