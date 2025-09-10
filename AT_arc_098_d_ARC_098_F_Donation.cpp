#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int u,v,w;
}e[MN];
int n,m,a[MN],b[MN],c[MN],pre[MN],val[MN],f[MN],sumb[MN],dtot,ch[MN][2];
bool vis[MN];

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

void initpre(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
    }
}

bool cmp(Edge x,Edge y){
    return x.w<y.w;
}

void buildexkru(){
    sort(e+1,e+1+m,cmp);
    dtot=n;
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru!=rv){
            ++dtot;
            pre[ru]=pre[rv]=dtot;
            ch[dtot][0]=ru;
            ch[dtot][1]=rv;
            val[dtot]=e[i].w;
        }
    }
}

void dodp(){
    for(int i=1;i<=n;i++){
        f[i]=b[i]+c[i];
        sumb[i]=b[i];
    }
    for(int i=n+1;i<=dtot;i++){
        sumb[i]=sumb[ch[i][0]]+sumb[ch[i][1]];
        f[i]=min(max(f[ch[i][0]],val[i])+sumb[i]-sumb[ch[i][0]],max(f[ch[i][1]],val[i])+sumb[i]-sumb[ch[i][1]]);
    }
}

signed main(){
    initpre();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        c[i]=max(a[i]-b[i],0ll);
    }
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v;
        e[i].w=max(c[e[i].u],c[e[i].v]);
    }
    buildexkru();
    dodp();
    cout<<f[dtot];

    return 0;
}