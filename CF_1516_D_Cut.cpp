#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,q,tot,mxr,ptot,nxt[MN],a[MN],prm[MN],f[MN][30];
vector<int> c[MN];
bool vis[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=min(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=f[l][0];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1,ret=1e9;
        if(mid>=fl) ret=query(ls,fl,fr);
        if(mid<fr) ret=min(ret,query(rs,fl,fr));
        return ret;
    }

#undef ls
#undef rs
}sg;

void init(){
    vis[1]=1;
    for(int i=2;i<=mxr;i++){
        if(vis[i]) continue;
        prm[++ptot]=i;
        c[i].push_back(ptot);
        for(int j=(i<<1);j<=mxr;j+=i){
            vis[j]=1;
            c[j].push_back(ptot);
        }
    } 
    for(int i=1;i<=ptot;i++){
        nxt[i]=n+1;
    }
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mxr=max(mxr,a[i]);
    }
    init();
    for(int i=0;i<=21;i++) f[n+1][i]=n+1;
    for(int i=n;i>=1;i--){
        f[i][0]=n+1;
        for(auto pt:c[a[i]]){
            f[i][0]=min(f[i][0],nxt[pt]);
            nxt[pt]=i;
        }
    }
    sg.build(1,1,n);
    for(int i=n;i>=1;i--){
        f[i][0]=sg.query(1,i,f[i][0]-1);
        for(int j=1;j<=20;j++){
            f[i][j]=f[f[i][j-1]][j-1];
        }
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        int p=x,ret=0;
        for(int i=20;i>=0;i--){
            if(f[p][i]<=y){
                p=f[p][i];
                ret+=1<<i;
            }
        }
        cout<<++ret<<'\n';
    }
    return 0;
}
