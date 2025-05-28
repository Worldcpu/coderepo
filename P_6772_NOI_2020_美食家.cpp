#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=260,NINF=-1e18;
struct Festival{
    int t,u,y;
}fst[MN];
int logt,n,m,T,K,tot,idx[MN][MN],c[MN];

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=NINF){
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                if(i==j) mat[i][j]=x;
                else mat[i][j]=NINF;
            }
        }
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<MN;i++){
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    if(mat[i][k]==NINF||x.mat[k][j]==NINF) continue;
                    ret.mat[i][j]=max(ret.mat[i][j],mat[i][k]+x.mat[k][j]);
                }
            }
        }
        return ret;
    }

}pw[55],A,B;

void initA(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=5;j++){
            idx[i][j]=++tot;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<5;j++){
            A.mat[idx[i][j]][idx[i][j+1]]=0;   
        }
    }
}

void initpw(Matrix x){
    pw[0]=x;
    for(int i=1;i<=logt;i++) pw[i]=pw[i-1]*pw[i-1];
}

bool cmp(Festival x,Festival y){
    return x.t<y.t;
}

Matrix ksmpw(Matrix a,int b){
    for(int i=0;i<=logt;i++){
        if((b>>i)&1){
            Matrix ret;
            for(int j=0;j<MN;j++){
                for(int k=0;k<MN;k++){
                    if(a.mat[1][k]==NINF||pw[i].mat[k][j]==NINF) continue;;
                    ret.mat[1][j]=max(ret.mat[1][j],a.mat[1][k]+pw[i].mat[k][j]);
                }
            }
            a=ret;
        }
    }
    return a;
}

signed main(){
    cin>>n>>m>>T>>K;
    logt=__lg(T);
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    initA();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        A.mat[idx[u][w]][idx[v][1]]=c[v];
    }
    for(int i=1;i<=K;i++){
        cin>>fst[i].t>>fst[i].u>>fst[i].y;
    }
    sort(fst+1,fst+1+K,cmp);
    initpw(A);
    B.mat[1][idx[1][1]]=c[1];
    int lst=0;
    for(int i=1;i<=K;i++){
        B=ksmpw(B,fst[i].t-lst);
        if(B.mat[1][idx[fst[i].u][1]]!=NINF) B.mat[1][idx[fst[i].u][1]]+=fst[i].y;
        lst=fst[i].t;
    }
    if(lst!=T) B=ksmpw(B,T-lst);
    if(B.mat[1][idx[1][1]]==NINF) cout<<-1;
    else cout<<B.mat[1][idx[1][1]];
    return 0;
}
