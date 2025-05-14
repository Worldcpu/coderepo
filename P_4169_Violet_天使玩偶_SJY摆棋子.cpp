#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,INF=0x3f3f3f3f;
struct Query
{
    int x,y,op,id;
}a[MN],b[MN],tmp[MN];
int n,m,mxlen,ans[MN];

struct mxBIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    int query(int x){
        int ret=-INF;
        while(x){
            ret=max(ret,t[x]);
            x-=lowbit(x);
        }
        return ret;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]=max(t[x],k);
            x+=lowbit(x);
        }
    }

    void clear(int x){
        while(x<MN&&t[x]){
            t[x]=-INF;
            x+=lowbit(x);
        }
    }

}bit;

void cdq(int l,int r){
    // cout<<l<<" "<<r<<'\n';
    if(l==r) return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(j<=r){
        while(b[i].x<=b[j].x&&i<=mid){
            if(b[i].op==1) bit.update(b[i].y,b[i].x+b[i].y);
            tmp[k++]=b[i++];
        }
        if(b[j].op==2){
            ans[b[j].id]=min(ans[b[j].id],b[j].x+b[j].y-bit.query(b[j].y));
        }
        tmp[k++]=b[j++];
    }
    for(int p=l;p<i;p++){
        if(b[p].op==1) bit.clear(b[p].y);
    }
    while(i<=mid) tmp[k++]=b[i++];
    for(int p=l;p<=r;p++) b[p]=tmp[p];
}

void solve(int x,int y){
    for(int i=1;i<=n+m;i++){
        b[i]=a[i];
        if(x) b[i].x=mxlen-b[i].x;
        if(y) b[i].y=mxlen-b[i].y;
    }
    cdq(1,n+m);
}

int main(){
    memset(bit.t,-0x3f,sizeof(bit.t));
    memset(ans,0x3f,sizeof(ans));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
        a[i].op=1;
        a[i].x++;
        a[i].y++;
        mxlen=max({mxlen,a[i].x,a[i].y});
    }
    for(int i=n+1;i<=n+m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        a[i].op=op;
        a[i].x=++x;
        a[i].y=++y;
        mxlen=max({mxlen,a[i].x,a[i].y});
        a[i].id=i;
    }
    mxlen++;
    solve(0,0);
    solve(1,0);
    solve(0,1);
    solve(1,1);
    for(int i=n+1;i<=n+m;i++){
        if(a[i].op==2) cout<<ans[i]<<'\n';
    }
    return 0;
}