#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15,INF=1e18;
struct Line{
    int k,b;
    
    int get(int x){
        return k*x+b;
    }
}st[MN];
int n,m,top,t[MN],sum[MN],q[MN],ql,qr,f[MN],g[MN],h[MN],dp[MN];

double getk(Line x,Line y){
    return (double)(y.b-x.b)/(x.k-y.k);
}

void dodp(int *f){
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+t[i];
    }
    top=0;
    st[++top]={0,0};
    for(int i=1;i<=n;i++){
        while(top>1&&st[top-1].get(i)>=st[top].get(i)) top--;
        f[i]=max(st[top].get(i)+(1ll*i*i+i)/2-sum[i],f[i-1]);
        Line tmp={-i,f[i]+((i*i-i))/2+sum[i]};
        while(top>1&&getk(tmp,st[top-1])>=getk(st[top],st[top-1])) top--;
        st[++top]=tmp;
    }
}

void solve(int l,int r){
    if(l==r){
        h[l]=1ll-t[l];
        return;
    }
    int mid=(l+r)>>1,mx=0,now=0;
    solve(l,mid);
    solve(mid+1,r);
    top=0;
    for(int i=l-1;i<mid;i++){
        Line tmp={-i,f[i]+((i*i-i))/2+sum[i]};
        while(top>1&&getk(tmp,st[top-1])>=getk(st[top],st[top-1])) top--;
        st[++top]=tmp;
    }
    mx=-INF,now=1;
    for(int i=r;i>mid;i--){
        while(now<top&&getk(st[now],st[now+1])>=i) now++;
        mx=max(mx,st[now].get(i)+(i*i+i)/2-sum[i]+g[i+1]);
        h[i]=max(h[i],mx);
    }
    top=0;
    for(int i=mid+1;i<=r;i++){
        Line tmp={-i,g[i+1]+((i*i+i))/2-sum[i]};
        while(top>1&&getk(tmp,st[top-1])>=getk(st[top],st[top-1])) top--;
        st[++top]=tmp;
    }
    mx=-INF,now=top;
    for(int i=l-1;i<mid;i++){
        while(now>1&&getk(st[now],st[now-1])<=i) now--;
        mx=max(mx,st[now].get(i)+(i*i-i)/2+sum[i]+f[i]);
        h[i+1]=max(h[i+1],mx);
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    dodp(f);
    reverse(t+1,t+1+n);
    dodp(g);
    reverse(g+1,g+1+n);
    reverse(t+1,t+1+n);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+t[i];
    }
    solve(1,n);
    cin>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        cout<<max(f[x-1]+g[x+1],h[x]+t[x]-y)<<'\n';
    }

    return 0;
}