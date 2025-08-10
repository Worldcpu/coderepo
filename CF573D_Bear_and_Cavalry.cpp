#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e4+15,MT=5,MV=1e6+15,INF=1e18;
int n,q,idw[MN],idh[MN],ban[MN];
pir w[MN],h[MN];

struct Matrix{
    int mat[MT][MT];

    Matrix(int x=-INF){
        for(int i=0;i<MT;i++){
            mat[i][i]=x;
            for(int j=0;j<MT;j++){
                if(i==j) continue;
                mat[i][j]=-INF;
            }
        }
    }

    friend Matrix operator *(const Matrix &x,const Matrix &y){
        Matrix ret;
        for(int i=0;i<MT;i++){
            for(int j=0;j<MT;j++){
                for(int k=0;k<MT;k++){
                    ret.mat[i][j]=max(ret.mat[i][j],x.mat[i][k]+y.mat[k][j]);
                }
            }
        }
        return ret;
    }

}mt[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r;
        Matrix val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[rs].val*t[ls].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void setmat(int p){
        if(t[p].l==t[p].r){
            t[p].val=mt[t[p].l];
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        setmat(ls);
        setmat(rs);
        pushup(p);
    }

    void modify(int p,int pos){
        if(t[p].l==t[p].r){
            t[p].val=mt[pos];
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos);
        else modify(rs,pos);
        pushup(p);
    }

    void update(int x){
        auto *mat=mt[x].mat;
        mat[2][1]=mat[3][2]=0;
        mat[2][2]=mat[2][3]=mat[3][1]=mat[3][3]=mat[1][1]=mat[1][2]=mat[1][3]=-INF;
        if(x>=1){
            mat[1][1]=w[x].first*h[x].first*(ban[x]!=x);
        }
        if(x>=2) mat[1][2]=max((w[x].first*h[x].first+w[x-1].first*h[x-1].first)*(ban[x]!=x)*(ban[x-1]!=x-1),(w[x].first*h[x-1].first+w[x-1].first*h[x].first)*(ban[x]!=x-1)*(ban[x-1]!=x));
        if(x>=3){
            int tmp[3]={0,1,2};
            do{
                int ret=0;
                for(int i=0;i<3;i++){
                    ret+=w[x-i].first*h[x-tmp[i]].first;
                }
                for(int i=0;i<3;i++){
                    ret*=(ban[x-i]!=x-tmp[i]);
                }
                mat[1][3]=max(mat[1][3],ret);
            }while(next_permutation(tmp,tmp+3));
        }
        for(int i=1;i<=3;i++){
            if(mat[1][i]==0) mat[1][i]=-INF;
        }
        modify(1,x);
    }

#undef ls
#undef rs
}sg;


signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>w[i].first;
        w[i].second=i;
    }
    for(int i=1;i<=n;i++){
        cin>>h[i].first;
        h[i].second=i;
    }
    sort(w+1,w+1+n);
    sort(h+1,h+1+n);
    for(int i=1;i<=n;i++){
        idw[w[i].second]=i;
        idh[h[i].second]=i;
    }
    for(int i=1;i<=n;i++){
        ban[i]=idh[w[i].second];
    }
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        sg.update(i);
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        x=idw[x],y=idw[y];
        swap(ban[x],ban[y]);
        for(int i=x;i<=min(x+2,n);i++){
            sg.update(i);
        }
        for(int i=y;i<=min(y+2,n);i++){
            sg.update(i);
        }
        auto *ret=sg.t[1].val.mat;
        cout<<max({ret[1][1],ret[1][2],ret[1][3]})<<'\n';
    }

    return 0;
}
