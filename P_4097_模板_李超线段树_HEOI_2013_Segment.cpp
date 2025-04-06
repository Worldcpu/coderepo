#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
#define pir pair<double,int>
using namespace std;
constexpr int MN=1e5+15,INF=1e9+7,PPM=4e4;
constexpr double eps=1e-10;

struct line{
    int l,r,xl,xr;
    double k,b;
}f[MN<<2];

struct node{
    int l,r,id;
}t[MN<<2];

int n,lst,tot;

double gety(line p,int x){
    if(p.xl<=x&&x<=p.xr){
        return p.k*x+p.b;
    }else return -INF;
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

pir _max(pir a,pir b){
    if(a.first-b.first>eps) return a;
    else if(b.first-a.first>eps) return b;
    else return a.second<b.second?a:b;
}



void update(int p,int fl,int fr,int id){
    if(t[p].l>=fl&&t[p].r<=fr){
        if(!t[p].id){
            t[p].id=id;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(gety(f[id],mid)-gety(f[t[p].id],mid)>eps){
            swap(id,t[p].id);
        }
        if(gety(f[id],t[p].l)-gety(f[t[p].id],t[p].l)>eps||(gety(f[id],t[p].l)==gety(f[t[p].id],t[p].l)&&id<t[p].id)){
            update(ls,fl,fr,id);
        }
        if(gety(f[id],t[p].r)-gety(f[t[p].id],t[p].r)>eps||(gety(f[id],t[p].r)==gety(f[t[p].id],t[p].r)&&id<t[p].id)){
            update(rs,fl,fr,id);
        }
        return;
    }
    int mid=(t[p].l+t[p].r)>>1;
    if(mid>=fl) update(ls,fl,fr,id);
    if(mid<fr) update(rs,fl,fr,id);
}

pir query(int p,int k){
    pir ret;
    if(t[p].id) ret=pir(gety(f[t[p].id],k),t[p].id);
    if(t[p].l==t[p].r) return ret;
    int mid=(t[p].l+t[p].r)>>1;
    if(mid>=k) ret=_max(ret,query(ls,k));
    else ret=_max(ret,query(rs,k));
    return ret; 
}

int main(){
    cin>>n;
    int op,k,x0,x1,y0,y1;
    build(1,1,PPM);
    while (n--)
    {
        cin>>op;
        if(!op){
            cin>>k;
            k=(k+lst-1)%39989+1;
            lst=query(1,k).second;
            cout<<lst<<'\n';
        }else{
            cin>>x0>>y0>>x1>>y1;
            x0=(x0+lst-1)%39989+1;
            x1=(x1+lst-1)%39989+1;
            y0=(y0+lst-1)%1000000000+1;
            y1=(y1+lst-1)%1000000000+1;
            tot++;
            if(x0==x1){
                f[tot].k=0;
                f[tot].b=max(y1,y0);
                f[tot].xl=f[tot].xr=x0;
            }else{
                f[tot].k=1.0*(1.0*y1-y0)/(x1-x0);
                f[tot].b=1.0*(1.0*y1-f[tot].k*x1);
                f[tot].xl=min(x0,x1);
                f[tot].xr=max(x0,x1);
            }
            update(1,f[tot].xl,f[tot].xr,tot);
        }
    }
    
    return 0;
}