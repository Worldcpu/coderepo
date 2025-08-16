#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2520+15,MT=9,INF=1e18;
int n,S,q;
pir qj[MN];

struct Matrix{
    int mat[9][9];

    Matrix(){
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                mat[i][j]=INF;
            }
            mat[i][i]=0;
        }
    }

    void init(){
        for(int k=0;k<=8;k++){
            for(int i=0;i<=8;i++){
                for(int j=0;j<=8;j++){
                    mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
                }
            }
        }
    }

    friend Matrix operator *(const Matrix &x,const Matrix &y){
        Matrix ret;
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                for(int k=0;k<=8;k++){
                    ret.mat[i][j]=min(ret.mat[i][j],x.mat[i][k]+y.mat[k][j]);
                }
            }
        }
        return ret;
    }

}A[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r;
        Matrix mat;
    }t[MN<<2];

    void pushup(int p){
        t[p].mat=t[ls].mat*t[rs].mat;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mat=A[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    Matrix query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mat;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr);
        if(mid>=fr) return query(ls,fl,fr);
        return query(ls,fl,fr)*query(rs,fl,fr);
    }

}sg;


signed main(){
    freopen("t4.in","r",stdin);
    freopen("t4.out","w",stdout);
    cin>>n>>S;
    for(int i=1;i<=n;i++){
        int p,u,v,w;
        cin>>p>>u>>v>>w;
        A[p].mat[u][v]=min(A[p].mat[u][v],w);
    }
    for(int i=1;i<=2000;i++) A[i].init();
    sg.build(1,1,2000);
    cin>>q;
    while(q--){
        int z,t,s;
        cin>>z>>t>>s;
        for(int i=1;i<=s;i++){
            cin>>qj[i].first>>qj[i].second;
        }
        sort(qj+1,qj+1+s);
        Matrix ret;
        for(int i=1;i<=s;i++){
            ret=ret*sg.query(1,qj[i].first,qj[i].second);
        }
        if(ret.mat[z][t]>=1e9) cout<<-1<<'\n';
        else cout<<ret.mat[z][t]<<'\n';
    }

    return 0;
}