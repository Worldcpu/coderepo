#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=0x3f3f3f3f;
int n,m,p[MN],c[MN],f[MN<<1],g[MN<<1],t[MN<<1],ans;

void upd(int &a,int &b,int x,int y){
    if(x<a) a=x,b=y;
}

void update(int x){
    f[x]=INF;
    if(c[x]) f[x]=0,g[x]=x;
    upd(f[x],g[x],f[x<<1]+(t[x<<1]<0?-1:1),g[x<<1]);
    upd(f[x],g[x],f[x<<1|1]+(t[x<<1|1]<0?-1:1),g[x<<1|1]);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=m;i++){
        cin>>p[i];
    }
    memset(f,0x3f,sizeof(f));
    for(int i=n;i>=1;i--){
        update(i);
    }
    for(int i=1;i<=m;i++){
        int x=INF,y=0,u=p[i],tt=0,vv=0;
        while(u){
            if(x>f[u]+tt){
                x=f[u]+tt;
                y=g[u],vv=u;
            }
            tt+=(t[u]>0?-1:1);
            u>>=1;
        }
        u=p[i];
        ans+=x;
        while(u!=vv){
            t[u]--;
            update(u>>1);
            u>>=1;
        }
        c[y]--;
        update(y);
        while(y!=vv){
            t[y]++;
            update(y>>1);
            y>>=1;
        }
        while(vv) update(vv),vv>>=1;
        cout<<ans<<' ';
    }
    return 0;
}