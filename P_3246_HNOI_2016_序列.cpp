#include<bits/stdc++.h>
#define pir pair<int,int>
#define ll long long
using namespace std;
constexpr int MN=5e6+15,NINF=-2e9,INF=2e9;
int n,m,top,a[MN],f[MN],s[MN],ans[MN];
vector<pir> q[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
#define ll long long
ll sum[MN],su_[MN];
int mx[MN],se[MN],c[MN],tag[MN],tc[MN];
ll ts[MN];

inline void pu(int p){
	mx[p]=max(mx[ls],mx[rs]);sum[p]=sum[ls]+sum[rs];su_[p]=su_[ls]+su_[rs];
	if(mx[ls]>mx[rs]){se[p]=max(se[ls],mx[rs]);c[p]=c[ls];}
	else if(mx[ls]<mx[rs]){se[p]=max(mx[ls],se[rs]);c[p]=c[rs];}
	else{se[p]=max(se[ls],se[rs]);c[p]=c[ls]+c[rs];}
}
inline void chg(int p,int k,int kc,ll ks){
	su_[p]+=kc*sum[p]+ks*c[p];sum[p]+=(ll)k*c[p];mx[p]+=k;
	tc[p]+=kc;ts[p]+=(ll)tag[p]*kc+ks;tag[p]+=k;
}
inline void pd(int p){
	if(tc[p]){
		int mxp=max(mx[ls],mx[rs]);
		if(mx[ls]==mxp)chg(ls,tag[p],tc[p],ts[p]);else chg(ls,0,tc[p],0);
		if(mx[rs]==mxp)chg(rs,tag[p],tc[p],ts[p]);else chg(rs,0,tc[p],0);
		tag[p]=tc[p]=ts[p]=0;
	}
}
void build(int p,int l,int r){
	if(l==r){sum[p]=mx[p]=a[l];c[p]=1;se[p]=-INF;return;}
	int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pu(p);
}
void upd(int p,int l,int r,int R,int k){
	if(k>=mx[p]&&r<=R)return chg(p,0,1,0);
	if(k<mx[p]&&r<=R&&k>se[p])return chg(p,k-mx[p],1,k-mx[p]);
	int mid=l+r>>1;
    pd(p);
    upd(ls,l,mid,R,k);
    if(R>mid)upd(rs,mid+1,r,R,k);
    pu(p);
}
ll qry(int p,int l,int r,int L,int R){		
	if(L<=l&&r<=R)return su_[p];
    int mid=l+r>>1;
    pd(p);
	if(L>mid)return qry(rs,mid+1,r,L,R);
    if(R<=mid)return qry(ls,l,mid,L,R);
    return qry(ls,l,mid,L,R)+qry(rs,mid+1,r,L,R);
}

}sg;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        q[r].push_back(pir(l,i));
    }
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        sg.upd(1,1,n,i,a[i]);
        for(auto p:q[i]){
            ans[p.second]=sg.qry(1,1,n,p.first,i);
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}
