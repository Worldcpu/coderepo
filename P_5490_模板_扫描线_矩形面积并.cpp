#include<bits/stdc++.h>
#define int long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;
struct scanline
{
    int l,r,h,dat;
    bool operator<(const scanline &a)const{
        if(h==a.h) return dat>a.dat;
        return h<a.h;
    }
}line[MN<<2];

int y[MN],n;

struct segtree{
    int l,r;
    int sum,len;
}t[MN<<2];

void pushup(int p){
    if(t[p].sum){
        t[p].len=y[t[p].r+1]-y[t[p].l];
    }else t[p].len=t[ls].len+t[rs].len;
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    t[p].sum=t[p].len=0; // 初始化
    if(l==r) return;
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

void update(int p,int fl,int fr,int k){
    if(y[t[p].r+1]<=fl||y[t[p].l]>=fr) return;
    if(y[t[p].l]>=fl&&y[t[p].r+1]<=fr){
        t[p].sum+=k;
        pushup(p);
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(y[mid]>=fl) update(ls,fl,fr,k);
    if(y[mid]<fr) update(rs,fl,fr,k);
    pushup(p);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        y[(i<<1)-1]=y1;
        y[i<<1]=y2;
        line[(i<<1)-1]={y1,y2,x1,1};
        line[(i<<1)]={y1,y2,x2,-1};
    }
    n<<=1;
    sort(y+1,y+1+n);
    sort(line+1,line+1+n);
    int m=unique(y+1,y+1+n)-y-1;
    build(1,1,m);
    int ans=0;
    for(int i=1;i<n;i++){
        update(1,line[i].l,line[i].r,line[i].dat);
        ans+=t[1].len*(line[i+1].h-line[i].h);
    }
    cout<<ans;
    return 0;
}
