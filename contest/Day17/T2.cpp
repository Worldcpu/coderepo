#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15,MOD=1e9+7;
int n,ans,id[MN],pw2[MN];
vector<int> adj[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
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

    int query(int p,int fl,int fr){
        if(fl>fr) return 0;
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1;
        int ret=0;
        if(mid>=fl) ret+=query(ls,fl,fr);
        if(mid<fr) ret+=query(rs,fl,fr);
        return ret;
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val+=k;
            assert(t[p].val>=0);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

}sg;

void dfs(int u,int pre,int maxx){
    sg.modify(1,u,1);
        ans+=max(sg.query(1,1,u-1)-1,0ll);
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u,maxx);
    }
    sg.modify(1,u,-1);
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    sg.build(1,1,n);
    dfs(1,0,0);
    cout<<ksm(2,ans);
    return 0;
}