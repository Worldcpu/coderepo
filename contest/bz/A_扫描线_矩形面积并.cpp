#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Line{
    int l,r,h,dat;
}ln[MN];
int X[MN],n,ans;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,sum,len;
    }t[MN<<2];

    void pushup(int p){
        if(t[p].sum){
            t[p].len=X[t[p].r+1]-X[t[p].l];
        }else{
            t[p].len=t[ls].len+t[rs].len;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        int l=t[p].l,r=t[p].r;
        if(fl>=X[r+1]||fr<=X[l]) return;
        if(X[l]>=fl&&X[r+1]<=fr){
            t[p].sum+=k;
            pushup(p);
            return;
        }
        int mid=(l+r)>>1;
        if(X[mid]>=fl) modify(ls,fl,fr,k);
        if(X[mid]<fr)  modify(rs,fl,fr,k);
        pushup(p);
    }
}sg;

bool cmp(Line x,Line y){
    return x.h<y.h;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        X[2*i-1]=x1,X[2*i]=x2;
        ln[2*i-1]={x1,x2,y1,1};
        ln[2*i]={x1,x2,y2,-1};
    }
    n<<=1;
    sort(ln+1,ln+1+n,cmp);
    sort(X+1,X+1+n);
    int tot=unique(X+1,X+1+n)-X-1;
    sg.build(1,1,tot-1);
    for(int i=1;i<n;i++){
        sg.modify(1,ln[i].l,ln[i].r,ln[i].dat);
        ans+=(sg.t[1].len)*(ln[i+1].h-ln[i].h);
    }
    cout<<ans;

    return 0;
}