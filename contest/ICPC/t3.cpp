#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,q;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mx=-1;
        multiset<int> q;
    }t[MN<<2];

    void pushup(int p){
        if(t[p].l==t[p].r) t[p].mx=-1;
        else t[p].mx=max(t[ls].mx,t[rs].mx);
        if(t[p].q.size()) t[p].mx=max(t[p].mx,*(--t[p].q.end()));
    }

    void pushdown(int p){
        if(t[p].q.empty()) return;
        int val=*(--t[p].q.end());
        t[p].q.erase(t[p].q.find(val));
        t[ls].q.insert(val);
        t[rs].q.insert(val);
        pushup(ls);
        pushup(rs);
    }

    void build(int p,int l,int r){
        t[p].l=l,t[p].r=r;
        t[p].mx=-1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            t[p].q.insert(k);
            t[p].mx=max(t[p].mx,k);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(fl<=mid) modify(ls,fl,fr,k);
        if(fr>mid) modify(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mx;
        }
        int mid=(t[p].l+t[p].r)>>1,mx=-1;
        if(fl<=mid) mx=max(mx,query(ls,fl,fr));
        if(fr>mid) mx=max(mx,query(rs,fl,fr));
        if(t[p].q.size()) mx=max(mx,*(--t[p].q.end()));
        return mx;
    }

    void modifyg(int p,int fl,int fr,int k){
        if(t[p].mx<k) return;
        if(t[p].l>=fl&&t[p].r<=fr&&t[p].q.size()&&*(--t[p].q.end())==k){
            t[p].q.erase(t[p].q.find(k));
            pushup(p);
            return;
        }
        if(t[p].q.size()&&*(--t[p].q.end())==k) pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(fl<=mid) modifyg(ls,fl,fr,k);
        if(fr>mid) modifyg(rs,fl,fr,k);
        pushup(p);
    }

}sg;

int main(){
    #ifndef ONLINE_JUDGE
    freopen("memory.in","r",stdin);
    freopen("memory.out","w",stdout);
    #endif
    cin>>n>>q;
    sg.build(1,1,n);
    while(q--){
        int op,l,r,k;
        cin>>op>>l>>r;
        if(op==1){
            cin>>k;
            sg.modify(1,l,r,k);
        }
        if(op==2){
            k=sg.query(1,l,r);
            if(k<0) continue; // 允许删除0
            sg.modifyg(1,l,r,k);
        }
        if(op==3){
            cout<<sg.query(1,l,r)<<'\n';
        }
    }
    return 0;
}
