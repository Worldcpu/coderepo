#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
const int INF=1e18;
int ans[MN],a[MN],n,m,rt[MN];
vector<int> adj[MN];
vector<pir> qry[MN];

struct Matrix{
    int mat[2][2];

    Matrix(int x=0){
        mat[0][0]=mat[0][1]=mat[1][0]=mat[1][1]=x;
    }

    Matrix(int x1,int y1,int x2,int y2){
        mat[0][0]=x1;mat[0][1]=y1;mat[1][0]=x2;mat[1][1]=y2;
    }

    Matrix(int x,int y){
        mat[0][0]=x;mat[1][1]=y;mat[0][1]=mat[1][0]=INF;
    }

    friend bool operator==(const Matrix &x,const Matrix &y){
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) if(x.mat[i][j]!=y.mat[i][j]) return 0;
        return 1;
    }

    friend Matrix operator*(const Matrix &x,const Matrix &y){
        Matrix ret(INF);
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++)
            ret.mat[i][j]=min(ret.mat[i][j],x.mat[i][k]+y.mat[k][j]);
        return ret;
    }
};
const Matrix MINF=Matrix(0,INF,INF,0);

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson;
        Matrix val;
    }t[MN*30];
    int tot;
    void init(int x){t[x].lson=t[x].rson=0;t[x].val=MINF;}

    void pushdown(int p){
        if(t[p].val==MINF) return;
        if(!ls) ls=++tot,init(ls);
        if(!rs) rs=++tot,init(rs);
        t[ls].val=t[ls].val*t[p].val;
        t[rs].val=t[rs].val*t[p].val;
        t[p].val=MINF;
    }

    void modify(int &p,int l,int r,int pos,const Matrix &k){
        if(!p) p=++tot,init(p);
        if(l==r){
            t[p].val=t[p].val*k;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(pos<=mid){
            modify(ls,l,mid,pos,k);
        }else{
            modify(rs,mid+1,r,pos,k);
        }
    }
    int merge(int x,int y){
        if(!x||!y) return x|y;
        if(!t[x].lson&&!t[x].rson) swap(x,y);
        if(!t[y].lson&&!t[y].rson){
            t[x].val=t[x].val*Matrix(t[y].val.mat[0][0],t[y].val.mat[0][1]);
            return x;
        }
        pushdown(x);
        pushdown(y);
        t[x].lson=merge(t[x].lson,t[y].lson);
        t[x].rson=merge(t[x].rson,t[y].rson);
        return x;
    }
    void solve(int p,int l,int r){
        if(l==r){
            ans[l]=t[p].val.mat[0][1];
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(ls) solve(ls,l,mid);
        if(rs) solve(rs,mid+1,r);
    }
}sg;

void dfs(int u,int pre){
    rt[u]=++sg.tot;
    sg.init(rt[u]);
    sg.t[rt[u]].val=Matrix(0,a[u],0,0);
    for(auto v:adj[u]) if(v!=pre){
        dfs(v,u);
        rt[u]=sg.merge(rt[u],rt[v]);
    }
    for(auto pr:qry[u]){
        if(pr.first==0) sg.modify(rt[u],1,m,pr.second,Matrix(0,INF));
        else sg.modify(rt[u],1,m,pr.second,Matrix(INF,0));
    }
    sg.t[rt[u]].val=sg.t[rt[u]].val*Matrix(INF,0,0,0);
}

signed main(){
    string tmp;
    cin>>n>>m>>tmp;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=m;i++){
        int x1,v1,x2,v2;
        cin>>x1>>v1>>x2>>v2;
        qry[x1].push_back({v1,i});
        qry[x2].push_back({v2,i});
    }
    sg.init(0);
    dfs(1,0);
    if(rt[1]) sg.solve(rt[1],1,m);
    for(int i=1;i<=m;i++) cout<<(ans[i]>=INF?-1:ans[i])<<'\n';
    return 0;
}
