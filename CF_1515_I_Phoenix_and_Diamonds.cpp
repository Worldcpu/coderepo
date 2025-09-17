#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MV=19,INF=1e18;
int w[MN],v[MN],a[MN],ord[MN],kuai,n,m,id[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,sw[MV+1],sv[MV+1],mnv[MV+1];
    }t[MN<<2];

    void pushup(int p){
        for(int i=0;i<=MV;i++){
            t[p].sw[i]=t[ls].sw[i]+t[rs].sw[i];
            t[p].sv[i]=t[ls].sv[i]+t[rs].sv[i];
            t[p].mnv[i]=min(t[ls].mnv[i],t[rs].mnv[i]+t[ls].sw[i]);
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int k){
        for(int i=0;i<=MV;i++){
            t[p].sw[i]=t[p].sv[i]=0;
            t[p].mnv[i]=INF;
            if(w[k]<(1<<i)){
                t[p].sw[i]+=a[k]*w[k];
                t[p].sv[i]+=a[k]*v[k];
            }else if(w[k]<(1<<i+1)&&a[k]){
                t[p].mnv[i]=w[k];
            }
        }
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            a[ord[t[p].l]]+=k;
            update(p,ord[t[p].l]);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int query(int p,int pos,int &k){
        if(t[p].l==t[p].r){
            int x=min(a[ord[t[p].l]],k/w[ord[t[p].l]]);
            k-=x*w[ord[t[p].l]];
            return v[ord[t[p].l]]*x;
        }
        int mid=(t[p].l+t[p].r)>>1;
        while(kuai&&(1<<(kuai-1))>k) kuai--;
        if(t[p].sw[kuai]<=k){
            return k-=t[p].sw[kuai],t[p].sv[kuai];
        }
        if(t[p].sw[kuai-1]<=k&&t[p].mnv[kuai-1]>k){
            return k-=t[p].sw[kuai-1],t[p].sv[kuai-1];
        }
        return query(ls,pos,k)+query(rs,pos,k);
    }

}sg;

bool cmp(int x,int y){
    return v[x]==v[y]?w[x]<w[y]:v[x]>v[y];
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>w[i]>>v[i];
        ord[i]=i;
    }
    sort(ord+1,ord+1+n,cmp);
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        id[ord[i]]=i;
        sg.modify(1,i,0);
    }
    while(m--){
        int op,x,y;
        cin>>op>>x;
        if(op==3){
            kuai=MV;
            cout<<sg.query(1,114514,x)<<'\n';
        }else{
            cin>>y;
            sg.modify(1,id[y],(op==1)?x:-x);
        }
    }
    return 0;
}