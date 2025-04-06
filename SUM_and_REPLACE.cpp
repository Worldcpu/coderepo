#include<iostream>
#define ls p<<1
#define rs p<<1|1
#define endl '\n'
#define ll long long
using namespace std;
const int MN=3e5+15,MNUM=1e6+16;
int ans[MNUM];
int n,m;
struct segtree
{
    int l,r;
    ll val;
    bool tag;
}t[4*MN];
ll a[MN];
inline void pushup(int p){
    t[p].val=t[ls].val+t[rs].val;
    if(t[ls].tag&&t[rs].tag){
        t[p].tag=1;
    }else t[p].tag=0;
}
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].val=a[l];
        if(t[p].val<=2){
            t[p].tag=1;
        }else t[p].tag=0;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
void modify(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr&&t[p].l==t[p].r){
        t[p].val=ans[t[p].val];
        if(t[p].val<=2){
            t[p].tag=1;
        }
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl&&!t[ls].tag){
        modify(ls,fl,fr);
    }
    if(mid<fr&&!t[rs].tag){
        modify(rs,fl,fr);
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
        ret+=query(ls,fl,fr);
    }
    if(mid<fr){
        ret+=query(rs,fl,fr);
    }
    return ret;
}
void pre(){
    for(int i=1;i<MNUM;i++){
        int t=0;
        for(int j=1;j*j<=i;j++){
            if(i%j==0){
                t++;
                if(j*j!=i){
                    t++;
                }
            }
        }
        ans[i]=t;
    }
}
int main(){
    ios::sync_with_stdio(0);
    pre();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1){
            modify(1,l,r);
        }else{
            cout<<query(1,l,r)<<endl;
        }
    }
    return 0;
}