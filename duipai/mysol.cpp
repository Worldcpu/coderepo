#include<bits/stdc++.h>
#define ll long long
#define pirl std::pair<int,int>
using namespace std;

constexpr int MN = 6e6 + 15; 
struct Query{
    bool op;
    ll x,y;
}qry[MN];

int n,m;
bool ans[MN];
ll MAXN;
vector<pirl> e[MN];

struct DSU{
    int pre[MN];

    void init(int tot){
        for(int i=0;i<=tot;i++) pre[i]=i;
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        return pre[x]=root(pre[x]);
    }

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        pre[rx]=ry;
    }

    bool isin(int x,int y){
        return root(x)==root(y);
    }
} dsu;

struct Segment{
    struct Node{
        int lson,rson,tag;
    }t[MN];

    int tot=1;

    bool isleaf(int x){
        return (!t[x].lson && !t[x].rson);
    }

    void pushdown(int p){
        if(!t[p].lson) t[p].lson=++tot;
        if(!t[p].rson) t[p].rson=++tot;
        if(t[p].tag){
            t[t[p].lson].tag=t[t[p].rson].tag=t[p].tag;
            t[p].tag=0;
        }
    }

    void modify(int p,ll l,ll r,ll fl,ll fr,int k){
        if(l>fr || r<fl) return;
        if(l>=fl && r<=fr){
            t[p].tag=k;
            return;
        }
        pushdown(p);
        ll mid=(l+r)>>1;
        modify(t[p].lson,l,mid,fl,fr,k);
        modify(t[p].rson,mid+1,r,fl,fr,k);
    }

    void link(int x,int y){
        if(isleaf(x)&&isleaf(y)){
            e[min(t[x].tag,t[y].tag)].push_back({x,y});
            return;
        }
        if(isleaf(x)){
            link(x,t[y].lson);
            link(x,t[y].rson);
        } else if(isleaf(y)){
            link(t[x].lson,y);
            link(t[x].rson,y);
        } else{
            link(t[x].lson,t[y].lson);
            link(t[x].rson,t[y].rson);
        }
    }

    int query(int p,ll l,ll r,ll pos){
        if(isleaf(p)) return p;
        ll mid=(l+r)>>1;
        if(pos<=mid) return query(t[p].lson,l,mid,pos);
        else return query(t[p].rson,mid+1,r,pos);
    }

} sg;

void initsol(){
    dsu.init(sg.tot);
    for(int i=1;i<=sg.tot;i++){
        if(!sg.isleaf(i)){
            sg.link(sg.t[i].lson,sg.t[i].rson);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    MAXN=(1ll<<n)-1;
    sg.t[1].tag=m+1;

    for(int i=1;i<=m;i++){
        string op;
        ll x,y;
        cin>>op>>x>>y;
        qry[i]={op[0]=='b',x,y};
    }

    for(int i=1;i<=m;i++){
        if(qry[i].op){
            sg.modify(1,0,MAXN,qry[i].x,qry[i].y,i);
        }
    }

    initsol();

    for(auto p:e[m+1]){
        dsu.merge(p.first,p.second);
    }

    for(int i=m;i>=1;i--){
        for(auto p:e[i]){
            dsu.merge(p.first,p.second);
        }
        if(!qry[i].op){
            ans[i]=dsu.isin(sg.query(1,0,MAXN,qry[i].x),sg.query(1,0,MAXN,qry[i].y));
        }
    }

    for(int i=1;i<=m;i++){
        if(!qry[i].op) cout<<ans[i]<<'\n';
    }
    return 0;
}
