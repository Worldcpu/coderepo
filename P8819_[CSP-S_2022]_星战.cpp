#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,q,hsum,now,st,h[MN],g[MN],c[MN];
mt19937 mt;

signed main(){
    mt.seed(time(0));
    cin>>n>>m;
    st=mt();
    for(int i=1;i<=n;i++){
        h[i]=(st+=mt());
        hsum+=h[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        g[v]+=h[u];
        c[v]=g[v];
        now+=h[u];
    }
    cin>>q;
    while(q--){
        int op,u,v;
        cin>>op;
        if(op==1){
            cin>>u>>v;
            now-=h[u];
            c[v]-=h[u];
        }
        if(op==2){
            cin>>u;
            now-=c[u];
            c[u]=0;
        }
        if(op==3){
            cin>>u>>v;
            now+=h[u];
            c[v]+=h[u];
        }
        if(op==4){
            cin>>u;
            now+=g[u]-c[u];
            c[u]=g[u];
        }
        if(now==hsum){
            cout<<"YES\n";
        }else cout<<"NO\n";
    }
    return 0;
}
