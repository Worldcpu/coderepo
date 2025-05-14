#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520,MQ=5e5+15,INF=1e9+7;
struct Query{
    int x1,y1,x2,y2,k,id;
}q[MQ],lq[MQ],rq[MQ];
int n,m,qtot,atot,tot,ans[MQ],a[MN];
struct ewBIT{
    int t[MN][MN];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int y,int k){
        for(int i=x;i<MN;i+=lowbit(i)){
            for(int j=y;j<MN;j+=lowbit(j)){
                t[i][j]+=k;
            }
        }
    }

    int query(int x,int y){
        int ret=0;
        for(int i=x;i;i-=lowbit(i)){
            for(int j=y;j;j-=lowbit(j)){
                ret+=t[i][j];
            }
        }
        return ret;
    }

}bit;

void solve(int l,int r,int st,int ed){
    if(st>ed) return;
    if(l==r){
        for(int i=st;i<=ed;i++){
            ans[q[i].id]=l;
        }
        return;
    }
    int mid=(l+r)>>1,lt=0,rt=0;
    for(int i=st;i<=ed;i++){
        if(!q[i].id){
            if(q[i].k<=mid) bit.update(q[i].x1,q[i].y1,1),lq[++lt]=q[i];
            else rq[++rt]=q[i];
        }else{
            int cnt=bit.query(q[i].x2,q[i].y2)-bit.query(q[i].x2,q[i].y1-1)-bit.query(q[i].x1-1,q[i].y2)+bit.query(q[i].x1-1,q[i].y1-1);
            if(cnt>=q[i].k) lq[++lt]=q[i];
            else q[i].k-=cnt,rq[++rt]=q[i];
        }
    }
    for(int i=ed;i>=st;i--) if(!q[i].id&&q[i].k<=mid) bit.update(q[i].x1,q[i].y1,-1);
    for(int i=1;i<=lt;i++) q[st+i-1]=lq[i];
    for(int i=1;i<=rt;i++) q[st+lt+i-1]=rq[i];
    solve(l,mid,st,st+lt-1);
    solve(mid+1,r,st+lt,ed);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x;
            cin>>x;
            q[++qtot]={i,j,0,0,x,0};
            a[++tot]=x;
        }
    }
    for(int i=1;i<=m;i++){
        int x1,y1,x2,y2,k;
        cin>>x1>>y1>>x2>>y2>>k;
        q[++qtot]={x1,y1,x2,y2,k,i};
    }
    solve(-INF,INF,1,qtot);
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}