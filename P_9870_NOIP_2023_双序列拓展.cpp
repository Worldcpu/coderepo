#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int c,q,n,m,ka,kb,x[MN],y[MN],a[MN],b[MN],pta[MN],ptb[MN],tmpa[MN],tmpb[MN];

bool check(int a[],int b[],int n,int m){
    if(a[1]<=b[1]) return 0;
    a[n+1]=INF;
    b[m+1]=-INF;
    int w=INF,pt=1;
    for(int i=1;i<=n;i++){
        for(w=min(w,a[i]);b[pt]>=w;)pt++;
        pta[i]=pt;
    }
    w=-INF,pt=1;
    for(int i=1;i<=m;i++){
        for(w=max(w,b[i]);a[pt]<=w;)pt++;
        ptb[i]=pt;
    }
    while(n>1&&m>1){
        if(pta[n]<m){
            m=pta[n];
        }else if(ptb[m]<n){
            n=ptb[m];
        }else return 0;
    }
    return 1;
}

bool solve(int a[],int b[],int n,int m){
    a[0]=-INF;b[0]=INF;
    int ta=0,tb=0;
    int mx=0,mn=0;
    for(int i=1;i<=n;i++){
        if(a[i]>a[mx]) mx=i;
    }
    for(int i=1;i<=m;i++){
        if(b[i]<b[mn]) mn=i; 
    }
    for(int i=1;i<=n;i++){
        if(a[i]<=b[mn]) return 0;
    }
    for(int i=1;i<=m;i++){
        if(b[i]>=a[mx]) return 0;
    }
    for(int i=1;i<=mx;i++) tmpa[++ta]=a[i];
    for(int i=1;i<=mn;i++) tmpb[++tb]=b[i];
    if(!check(tmpa,tmpb,ta,tb)) return 0;
    ta=tb=0;
    for(int i=n;i>=mx;i--){
        tmpa[++ta]=a[i];
    }
    for(int i=m;i>=mn;i--){
        tmpb[++tb]=b[i];
    }
    if(!check(tmpa,tmpb,ta,tb)) return 0;
    return 1;
}

int main(){
    cin>>c>>n>>m>>q;
    for(int i=1;i<=n;i++){
        cin>>x[i];
    }
    for(int i=1;i<=m;i++){
        cin>>y[i];
    }
    bool flag=0;
    q++;
    while(q--){
        for(int i=1;i<=n;i++){
            a[i]=x[i];
        }
        for(int i=1;i<=m;i++){
            b[i]=y[i];
        }
        if(!flag){
            flag=1;
            goto awa;
        }
        cin>>ka>>kb;
        for(int i=1,p;i<=ka;i++){
            cin>>p>>a[p];
        }
        for(int i=1,p;i<=kb;i++){
            cin>>p>>b[p];
        }
awa:
        if(a[1]>b[1]) cout<<solve(a,b,n,m);
        else cout<<solve(b,a,m,n);
    }
    return 0;
}
