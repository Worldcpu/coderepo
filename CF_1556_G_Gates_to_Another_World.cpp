#include<bits/stdc++.h>
#define ll long long
#define pirl pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
struct Query{
    bool op;
    ll x,y;
}qry[MN];
int n,m;
bool ans[MN];
ll MAXN;
vector<pirl> e[MN];

struct DSU{
    int pre[MN<<6];

    void init(int tot){
        for(int i=0;i<=tot;i++) pre[i]=i;
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        pre[ry]=rx;
    }

    bool isin(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return 1;
        return 0;
    }

}dsu;

struct Segment{
    #define ls(p) (t[p].lson)
    #define rs(p) (t[p].rson)
    struct Node{
        int lson,rson,tag;
    }t[MN<<6];
    int tot=1;

    bool isleaf(int x){
        return (!ls(x)&&!rs(x));
    }

    void pushdown(int p){
        if(!ls(p)) ls(p)=++tot;
        if(!rs(p)) rs(p)=++tot;
        if(t[p].tag){
            t[ls(p)].tag=t[rs(p)].tag=t[p].tag;
            t[p].tag=0;
        }
    }

    void modify(int p,ll l,ll r,ll fl,ll fr,int k){
        if(l>=fl&&r<=fr){
            t[p].tag=k;
            return;
        }
        pushdown(p);
        ll mid=(l+r)>>1;
        if(mid>=fl) modify(ls(p),l,mid,fl,fr,k);
        if(mid<fr) modify(rs(p),mid+1,r,fl,fr,k);
    }

    void link(int x,int y){
        if(isleaf(x)&&isleaf(y)){
            e[min(t[x].tag,t[y].tag)].push_back(pirl(x,y));
        }
        else if(isleaf(x)){
            link(x,ls(y));
            link(x,rs(y));
        }else if(isleaf(y)){
            link(ls(x),y);
            link(rs(x),y);
        }else{
            link(ls(x),ls(y));
            link(rs(x),rs(y));
        }
    }

    int query(int p,ll l,ll r,ll pos){
        if(isleaf(p)){
            return p;
        }
        ll mid=(l+r)>>1;
        if(mid>=pos) return query(ls(p),l,mid,pos);
        else return query(rs(p),mid+1,r,pos);
    }
}sg;

void initsol(){
    dsu.init(sg.tot);
    for(int i=1;i<=sg.tot;i++){
        if(!sg.isleaf(i)){
            sg.link(sg.t[i].lson,sg.t[i].rson);
        }
    }
}

int main(){
    cin>>n>>m;
    MAXN=(1ll<<n)-1;
    sg.t[1].tag=m+1;
    for(int i=1;i<=m;i++){
        string op;
        cin>>op>>qry[i].x>>qry[i].y;
        qry[i].op=op[0]=='b';
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