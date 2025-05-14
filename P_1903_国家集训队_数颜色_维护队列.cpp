#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e6+15;
struct Change{
    int pos,k;
}c[MN];
struct Query{
    int l,r,t,id;
}q[MN];
int n,m,ctot,qtot,len,ret,l,r,now,a[MN],cnt[MN],ans[MN];

bool cmp(Query x,Query y){
    if(x.l/len!=y.l/len) return x.l<y.l;
    if(x.r/len!=y.r/len) return x.r<y.r;
    return x.t<y.t;
}

void add(int k){
    if(++cnt[k]==1){ ret++;}
}

void del(int k){
    if(--cnt[k]==0) ret--;
}

void update(int p){
    if(c[p].pos>=l&&c[p].pos<=r){
        del(a[c[p].pos]);
        add(c[p].k);
    }
    swap(a[c[p].pos],c[p].k);
}

int main(){
    cin>>n>>m;
    len=cbrt(n)*cbrt(n);
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='Q'){
            qtot++;
            q[qtot].l=x;
            q[qtot].r=y;
            q[qtot].t=ctot;
            q[qtot].id=qtot;
        }else{
            ctot++;
            c[ctot].pos=x;
            c[ctot].k=y;
        }
    }
    sort(q+1,q+1+qtot,cmp);
    l=1,r=0,now=0;
    for(int i=1;i<=qtot;i++){
        while(now<q[i].t) update(++now);
        while(now>q[i].t) update(now--);
        while(l>q[i].l){
            l--;
            add(a[l]);
        }
        while(r<q[i].r){
            r++;
            add(a[r]);
        }
        while(l<q[i].l){
            del(a[l]);
            l++;
        }
        while(r>q[i].r){
            del(a[r]);
            r--;
        }
        ans[q[i].id]=ret;
    }
    for(int i=1;i<=qtot;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}