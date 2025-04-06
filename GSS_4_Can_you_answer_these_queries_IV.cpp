#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int MN=1e5+15;
struct segtree
{
    ll val;
    int l,r;
    bool tag=0;
}t[4*MN];
ll a[MN];
int n,m,cnt=0;
inline void pushup(int p){
    t[p].val=t[p<<1].val+t[p<<1|1].val;
    if(t[p<<1].tag&&t[p<<1|1].tag){
        t[p].tag=1;
    }else t[p].tag=0;
}
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    t[p].tag=0;
    t[p].val=0;
    if(l==r){
        t[p].val=a[l];
        if(a[l]==0||a[l]==1){
            t[p].tag=1;
        }else t[p].tag=0;
        return;
    }
    int mid=l+r>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
}
void sq(int p,int fl,int fr){
    if(t[p].tag) return;
    if(t[p].l==t[p].r){
        t[p].val=sqrt(t[p].val);
        if(t[p].val==0||t[p].val==1){
            t[p].tag=1;
        }
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl&&!t[p<<1].tag){
        sq(p<<1,fl,fr);
    }
    if(mid<fr&&!t[p<<1|1].tag){
        sq(p<<1|1,fl,fr);
    }
    pushup(p);
}
ll query(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].val;
    }
    ll ret=0;
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl){
        ret+=query(p<<1,fl,fr);
    }
    if(mid<fr){
        ret+=query(p<<1|1,fl,fr);
    }
    return ret;
}
signed main(){
    // ios::sync_with_stdio(0);
    while (cin>>n)
    {
        // memset(a,0,sizeof(a));
        // memset(t,0,sizeof(t));
        cout<<"Case #"<<++cnt<<endl;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        build(1,1,n);
        cin>>m;
        for(int i=1;i<=m;i++){
            int op,l,r;
            cin>>op>>l>>r;
            if(l>r) swap(l,r);
            if(op==1){
                cout<<query(1,l,r)<<endl;
            }else sq(1,l,r);
        }
        cout<<endl;
    }
    
    return 0;
}