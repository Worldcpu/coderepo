#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,INF=1e9;
int n,m,a[MN],b[MN],f[MN];

struct segtree{
    #define ls p<<1
    #define rs p<<1|1
    int maxx[MN<<2],val[MN<<2],ans[MN<<2];

    void build(){
        memset(maxx,-127,sizeof(maxx));
        memset(val,127,sizeof(val));
        memset(ans,127,sizeof(ans));
    }

    int query(int p,int l,int r,int fl,int fr,int &k){
        if(fl>fr||k>=maxx[p]||val[p]>=INF) return INF;

        int mid=(l+r)>>1,ret=INF;
        if(l>=fl&&r<=fr){
            if(l==r) return k=maxx[p],val[p];
            if(maxx[rs]>k){
                ret=query(rs,mid+1,r,fl,fr,k);
                ret=min(ret,ans[p]);
                k=max(k,maxx[ls]);
                return ret;
            }else return query(ls,l,mid,fl,fr,k);
        }
        if(mid<fr) ret=min(ret,query(rs,mid+1,r,fl,fr,k));
        if(mid>=fl) ret=min(ret,query(ls,l,mid,fl,fr,k));
        
        return ret;
    }

    void update(int p,int l,int r,int pos,int k){
        if(l==r){
            maxx[p]=k;
            val[p]=f[k];
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) update(ls,l,mid,pos,k);
        else update(rs,mid+1,r,pos,k);
        val[p]=min(val[ls],val[rs]);
        maxx[p]=max(maxx[ls],maxx[rs]);
        int awa=maxx[rs];
        ans[p]=query(ls,l,mid,l,mid,awa);
    }

    #undef ls 
    #undef rs
}sg;

int main(){
    freopen("revenge.in","r",stdin);
    freopen("revenge.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    a[n+1]=n+1;
    sg.build();
    sg.update(1,0,n+1,0,0);
    for(int i=1;i<=n+1;i++){
        int k=-INF;
        f[i]=sg.query(1,0,n+1,0,a[i]-1,k)+b[i];
        sg.update(1,0,n+1,a[i],i);
    }
    cout<<f[n+1];
    return 0;
}