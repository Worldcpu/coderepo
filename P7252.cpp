#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int b[MN],c[MN],n,m,tot,rt[MN];

struct Segment{
    struct Node{
        int lson,rson,val;
    }t[MN*50];
    int tot;

    void update(int &p,int lst,int l,int r,int k){
        p=++tot;
        t[p]=t[lst];
        t[p].val++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(mid>=k) update(t[p].lson,t[lst].lson,l,mid,k);
        else update(t[p].rson,t[lst].rson,mid+1,r,k);
    }

    int query(int x,int y,int l,int r,int k){
        if(l==r) return b[l];
        int mid=(l+r)>>1;
        int vx=abs(t[t[y].lson].val-t[t[x].lson].val),vy=abs(t[t[y].rson].val-t[t[x].rson].val);
        if(vx>k) return query(t[x].lson,t[y].lson,l,mid,k);
        if(vy>k) return query(t[x].rson,t[y].rson,mid+1,r,k); 
        return 0;
    }

}sg;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        b[i]=c[i];
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        c[i]=lower_bound(b+1,b+1+tot,c[i])-b;
        sg.update(rt[i],rt[i-1],1,tot,c[i]);       
    }
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<sg.query(rt[l-1],rt[r],1,tot,(r-l+1)/2)<<'\n';
    }
    return 0;
}