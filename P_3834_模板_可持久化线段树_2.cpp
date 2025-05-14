#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15,INF=1e9;
struct Query{
    int x,y,z,id;
}q[MN],lq[MN],rq[MN];
int n,m,qtot,a[MN],ans[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

}bit;

void solve(int l,int r,int st,int ed){
    if(st>ed) return;
    if(l==r){
        for(int i=st;i<=ed;i++){
            if(q[i].id) ans[q[i].id]=l;
        }
        return;
    }
    int mid=(l+r)>>1,lt=0,rt=0;
    for(int i=st;i<=ed;i++){
        if(q[i].id==0){
            if(q[i].y<=mid){
                bit.update(q[i].x,1);
                lq[++lt]=q[i];
            }else rq[++rt]=q[i];
        }else{
            int cnt=bit.query(q[i].y)-bit.query(q[i].x-1);
            if(cnt>=q[i].z) lq[++lt]=q[i];
            else q[i].z-=cnt,rq[++rt]=q[i];
        }
    }
    for(int i=ed;i>=st;i--) if(q[i].id==0&&q[i].y<=mid) bit.update(q[i].x,-1);
    for(int i=1;i<=lt;i++) q[st+i-1]=lq[i];
    for(int i=1;i<=rt;i++) q[st+lt+i-1]=rq[i];
    solve(l,mid,st,st+lt-1);
    solve(mid+1,r,st+lt,ed);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        q[++qtot]={i,a[i],0,0};
    }
    for(int i=1;i<=m;i++){
        int l,r,k;
        cin>>l>>r>>k;
        q[++qtot]={l,r,k,i};
    }
    solve(-INF,INF,1,qtot);
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}