#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,a[MN],b[MN],c[MN],d[MN];

int solve(){
    int f0=0,f1=0;
    for(int i=1;i<=m;i++){
        f0+=c[i],f1+=(!d[i]);
    }
    int g0,g1;
    for(int i=1;i<=n;i++){
        g0=f0,g1=f1;
        f0=min(g0,g1+m)+a[i]+b[i];
        f1=min(g0+m,g1)+(!a[i])+(!b[i]);
    }
    for(int i=1;i<=m;i++){
        f0+=d[i];
        f1+=(!d[i]);
    }
    return min(f0,f1);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        char neruo;
        cin>>neruo;
        a[i]=neruo=='R';
    }
    for(int i=1;i<=n;i++){
        char jimmy;
        cin>>jimmy;
        b[i]=jimmy=='R';
    }
    for(int i=1;i<=m;i++){
        char webnie;
        cin>>webnie;
        c[i]=webnie=='R';
    }
    for(int i=1;i<=n;i++){
        char RL;
        cin>>RL;
        d[i]=RL=='R';
    }
    int ans=solve();
    swap(n,m);
    swap(a,b),swap(c,d);
    cout<<min(ans,solve());
    return 0;
}
