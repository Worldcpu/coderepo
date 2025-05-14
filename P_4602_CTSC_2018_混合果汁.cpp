#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4e5+15,INF=LONG_LONG_MAX;
struct Query{
    int g,l,id;
}q[MN],lq[MN],rq[MN];
struct Node{
    int d,p,l;
}a[MN];
int n,m,ans[MN];

bool cmp(Node x,Node y){
    return x.d>y.d;
}

struct BIT
{
    int t[MN],c[MN],sum;

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int k){
        int v=x*k;
        sum+=k;
        while(x<MN){
            t[x]+=k;
            c[x]+=v;
            x+=lowbit(x);
        }
    }

    int query(int x){
        if(x>sum) return INF;
        int p=0,s=0;
        for(int i=20;i>=0;i--){
            int np=p+(1<<i);
            if(np>=MN||t[np]>=x) continue;
            p=np;
            x-=t[np];
            s+=c[np];
        }
        return s+(p+1)*x;
    }

}bit;

void solve(int l,int r,int st,int ed){
    if(st>ed) return;
    if(l==r){
        if(l>n) return;
        for(int i=st;i<=ed;i++){
            ans[q[i].id]=a[l].d;
        }
        return;
    }
    int mid=(l+r)>>1,lt=0,rt=0;
    for(int i=l;i<=mid;i++){
        bit.update(a[i].p,a[i].l);
    }
    for(int i=st;i<=ed;i++){
        int cnt=bit.query(q[i].l);
        if(cnt<=q[i].g) lq[++lt]=q[i];
        else rq[++rt]=q[i];
    }
    for(int i=1;i<=lt;i++) q[st+i-1]=lq[i];
    for(int i=1;i<=rt;i++) q[st+lt+i-1]=rq[i];
    solve(mid+1,r,st+lt,ed);
    for(int i=l;i<=mid;i++){
        bit.update(a[i].p,-a[i].l);
    }
    solve(l,mid,st,st+lt-1);
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].d>>a[i].p>>a[i].l;
    }
    for(int i=1;i<=m;i++){
        cin>>q[i].g>>q[i].l;
        q[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    memset(ans,-1,sizeof(ans));
    solve(1,n+1,1,m);
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}