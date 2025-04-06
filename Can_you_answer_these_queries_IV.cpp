#include<iostream>
#include<cmath>
#define ll long long
#define int long long
#define endl '\n'
using namespace std;
const int MN=1e5+15;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
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
    while (~scanf("%lld",&n)){
        cout<<"Case #"<<++cnt<<'\n';
        for(int i=1;i<=n;i++){
            a[i]=read();
        }
        build(1,1,n);
        m=read();
        for(int i=1;i<=m;i++){
            int op=read(),l=read(),r=read();
            // cin>>op>>l>>r;
            if(l>r) swap(l,r);
            if(op==1){
                cout<<query(1,l,r)<<'\n';
            }else sq(1,l,r);
        }
        puts("");
    }
    return 0;
}