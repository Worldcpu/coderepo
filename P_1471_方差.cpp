#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;
int n,m;
struct segtree
{
    int l,r;
    double sum,pfsum,tag;
}t[MN<<2];
void pushup(int p){
    t[p].sum=t[ls].sum+t[rs].sum;
    t[p].pfsum=t[ls].pfsum+t[rs].pfsum;
}
void pushdown(int p){
    if(t[p].tag){

        t[ls].pfsum+=2*t[p].tag*t[ls].sum+(t[ls].r-t[ls].l+1)*(t[p].tag*t[p].tag);
        t[rs].pfsum+=2*t[p].tag*t[rs].sum+(t[rs].r-t[rs].l+1)*(t[p].tag*t[p].tag);
        t[ls].sum+=(t[ls].r-t[ls].l+1)*t[p].tag;
        t[rs].sum+=(t[rs].r-t[rs].l+1)*t[p].tag;
        t[ls].tag+=t[p].tag;
        t[rs].tag+=t[p].tag;
        t[p].tag=0;
    }
}
double a[MN];
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].sum=a[l];
        t[p].pfsum=a[l]*a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

void update(int p,int fl,int fr,double k){
    if(t[p].l>=fl&&t[p].r<=fr){

        t[p].tag+=k;
        t[p].pfsum+=2*k*t[p].sum+(t[p].r-t[p].l+1)*k*k;
        t[p].sum+=(t[p].r-t[p].l+1)*k;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) update(ls,fl,fr,k);
    if(mid<fr) update(rs,fl,fr,k);
    pushup(p);
}

double querysum(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].sum;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    double ret=0;
    if(mid>=fl) ret+=querysum(ls,fl,fr);
    if(mid<fr) ret+=querysum(rs,fl,fr);
    return ret;
}

double querypfsum(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].pfsum;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    double ret=0;
    if(mid>=fl) ret+=querypfsum(ls,fl,fr);
    if(mid<fr) ret+=querypfsum(rs,fl,fr);
    return ret;
}

// void output(int p,int fl,int fr){
//     pushdown(p);
//     cout<<"l:"<<t[p].l<<" r:"<<t[p].r<<" sum:"<<t[p].sum<<" pfsum:"<<t[p].pfsum<<'\n';
//     int mid=t[p].l+t[p].r>>1;
//     if(mid>=fl) output(ls,fl,fr);
    
//     if(mid<fr) output(rs,fl,fr);
// }

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    int op,x,y;
    double k;
    while (m--)
    {
        cin>>op>>x>>y;
        if(op==1){
            cin>>k;
            update(1,x,y,k);
        }else if(op==2){
            cout<<fixed<<setprecision(4)<<querysum(1,x,y)/((y-x+1)*1.0)<<'\n';
        }else{
            cout<<fixed<<setprecision(4)<<(querypfsum(1,x,y)/((y-x+1)*1.0))-(querysum(1,x,y)/((y-x+1)*1.0))*(querysum(1,x,y)/((y-x+1)*1.0))<<'\n';
        }
        // output(1,1,n);
    }
    
    return 0;
}