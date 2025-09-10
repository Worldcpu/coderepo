#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int n,q,a[MN],v[15];

int findpos(int x){
    return lower_bound(v+1,v+11,x)-v; 
}

struct Segment{
    #define ls (p<<1)
    #define rs (p<<1|1)
    struct Node{
        int l,r,mn,cov,covid,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].mn=min(t[ls].mn,t[rs].mn);
    }

    void docov(int p,int cpos,int cid){
        t[p].mn=t[p].cov=cpos;
        t[p].covid=cid;
        t[p].add=0;
    }

    void doadd(int p,int k){
        if(!t[p].covid){
            t[p].mn-=k;
            t[p].add+=k;
            return;
        }
        t[p].cov-=k;
        while(t[p].cov<0){
            if(t[p].covid+1>10){ 
                t[p].cov=0; 
                break; 
            }
            t[p].cov+=v[t[p].covid+1]-v[t[p].covid];
            t[p].covid++;
        }
        t[p].mn=t[p].cov;
    }

    void pushdown(int p){
        if(t[p].covid){
            docov(ls,t[p].cov,t[p].covid);
            docov(rs,t[p].cov,t[p].covid);
            t[p].cov=t[p].covid=0;
        }
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].mn=t[p].cov=t[p].covid=t[p].add=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void cover(int p,int fl,int fr,int cpos,int cid){
        if(t[p].r<fl || t[p].l>fr) return;
        if(t[p].l>=fl && t[p].r<=fr){
            docov(p,cpos,cid);
            return;
        }
        pushdown(p);
        cover(ls,fl,fr,cpos,cid);
        cover(rs,fl,fr,cpos,cid);
        pushup(p);
    }

    void add(int p,int fl,int fr,int k){
        if(t[p].r<fl || t[p].l>fr) return;
        if(t[p].l>=fl && t[p].r<=fr && (t[p].mn>=k || t[p].covid)){
            doadd(p,k);
            return;
        }
        pushdown(p);
        add(ls,fl,fr,k);
        add(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int pos){
        if(t[p].l==t[p].r) return v[t[p].covid]-t[p].mn;
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return query(ls,pos);
        else return query(rs,pos);
    }

    int querymn(int p,int fl,int fr){
        if(t[p].r<fl || t[p].l>fr) return INF;
        if(t[p].l>=fl && t[p].r<=fr) return t[p].mn;
        pushdown(p);
        return min(querymn(ls,fl,fr), querymn(rs,fl,fr));
    }

}sg;

void init(){
    v[0]=1;
    for(int i=1;i<=10;i++) v[i]=v[i-1]*42;
}

signed main(){
    init();
    cin>>n>>q;
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        int idx=findpos(a[i]);
        sg.cover(1,i,i,v[idx]-a[i],idx);
    }
    while(q--){
        int op,x,y,z;
        cin>>op>>x;
        if(op==1){
            cout<<sg.query(1,x)<<'\n';
        }
        else if(op==2){
            cin>>y>>z;
            int idx=findpos(z);
            sg.cover(1,x,y,v[idx]-z,idx);
        }
        else if(op==3){
            cin>>y>>z;
            int cnt=0;
            do{
                sg.add(1,x,y,z);
                cnt++;
            }while(sg.querymn(1,x,y)<=0);
        }
    }
    return 0;
}
