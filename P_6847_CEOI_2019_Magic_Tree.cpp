#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,m,K,rt[MN],d[MN],w[MN];
vector<int> adj[MN];

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson=0,rson=0;
        int mx=0,mn=0,add=0;
    }t[MN*50];
    int tot=0;

    bool isleaf(int p){
        if(!p) return true;
        return !t[p].lson && !t[p].rson;
    }

    void doadd(int p,int k){
        if(!p) return;
        t[p].mn += k;
        t[p].mx += k;
        t[p].add += k;
    }

    void pushup(int p){
        int L=t[p].lson, R=t[p].rson;
        int mxL = L? t[L].mx : INT_MIN/2;
        int mxR = R? t[R].mx : INT_MIN/2;
        int mnL = L? t[L].mn : INT_MAX/2;
        int mnR = R? t[R].mn : INT_MAX/2;
        t[p].mx = max(mxL,mxR);
        t[p].mn = min(mnL,mnR);
        if(t[p].mx==t[p].mn){
            t[p].lson = t[p].rson = 0;
            t[p].add = 0;
        }
    }

    void pushdown(int p){
        if(!p) return;
        if(t[p].add){
            doadd(t[p].lson,t[p].add);
            doadd(t[p].rson,t[p].add);
            t[p].add=0;
        }
    }

    int merge(int x,int y){
        if(!x || !y) return x?x:y;
        if(isleaf(y)){
            doadd(x,t[y].mx);
            return x;
        }
        if(isleaf(x)){
            doadd(y,t[x].mx);
            return y;
        }
        pushdown(x);
        pushdown(y);
        t[x].lson = merge(t[x].lson, t[y].lson);
        t[x].rson = merge(t[x].rson, t[y].rson);
        pushup(x);
        return x;
    }

    int query(int p,int l,int r,int k){
        if(!p) return 0;
        if(isleaf(p)) return t[p].mx;
        pushdown(p);
        int mid=(l+r)>>1;
        if(k<=mid) return query(t[p].lson,l,mid,k);
        else return query(t[p].rson,mid+1,r,k);
    }

    void modify(int &p,int l,int r,int fl,int fr,int k){
        // non-overlap
        if(l>fr || r<fl || !p) return;
        // if current interval's min already >= k, nothing to do
        if(t[p].mn >= k) return;
        // fully covered and max <= k -> set to k and clear children
        if(l>=fl && r<=fr && t[p].mx <= k){
            t[p].mx = t[p].mn = k;
            t[p].lson = t[p].rson = t[p].add = 0;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(isleaf(p)){
            t[p].lson = ++tot;
            t[p].rson = ++tot;
            t[t[p].lson].mx = t[t[p].lson].mn = t[t[p].rson].mx = t[t[p].rson].mn = t[p].mx;
            // add/add initialized to 0 by Node default
        }
        if(fl <= mid) modify(t[p].lson, l, mid, fl, fr, k);
        if(fr > mid) modify(t[p].rson, mid+1, r, fl, fr, k);
        pushup(p);
    }

}sg;

void dfs(int u,int pre){
    rt[u] = ++sg.tot;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        rt[u] = sg.merge(rt[u], rt[v]);
    }
    if(d[u]){
        int cur = sg.query(rt[u],1,K,d[u]);
        int val = w[u] + cur;
        sg.modify(rt[u],1,K,d[u],K,val);
    }
}

signed main(){
    cin>>n>>m>>K;
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa;
        adj[fa].push_back(i);
        adj[i].push_back(fa);
    }
    for(int i=1;i<=m;i++){
        int x;
        cin>>x>>d[x]>>w[x];
    }
    dfs(1,0);
    cout<<sg.t[rt[1]].mx<<"\n";
    return 0;
}
