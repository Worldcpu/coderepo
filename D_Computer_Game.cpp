#include<bits/stdc++.h>
#define ll long long
#define double long double
using namespace std;
constexpr int MN=6e5+15;
constexpr double eps=1e-13;
struct Node{
    double k,b;
}ln[MN],cl[MN],s[MN];
ll n,t,top,tot,now;
double v;

struct Matrix{
    double mat[5][5];

    Matrix operator *(const Matrix &x)const{
        Matrix ret;
        memset(ret.mat,0,sizeof(ret.mat));
        for(int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){
                for(int k=1;k<=3;k++){
                    ret.mat[i][j]+=mat[i][k]*x.mat[k][j];
                }
            }
        }
        return ret;
    }

}g[40],f;

bool cmp(Node x,Node y){
    if(fabs(x.k-y.k)<eps) return x.b<y.b;
    return x.k<y.k;
}

int ck(double x){
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}

double gety(Node x,Node y){
    return (x.b-y.b)/(y.k-x.k);
}

int main(){
    cin>>n>>t;
    for(int i=1;i<=n;i++){
        double a,b,p;
        cin>>a>>b>>p;
        v=max(v,b*p);
        ln[i].k=p;
        ln[i].b=p*a;
    }
    sort(ln+1,ln+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(i == n || ck(ln[i].k - ln[i+1].k) != 0) cl[++tot]=ln[i];
    }
    for(int i=1;i<=tot;i++){
        while(top>1&&ck(gety(s[top],s[top-1])-gety(cl[i],s[top-1]))>=0) top--;
        s[++top]=cl[i];
    }
    f.mat[1][3]=1;
    for(int i=1;i<=top;i++){
        double x=now*v-f.mat[1][1];
        while(i<top&&ck(x-gety(s[i],s[i+1]))>=0) i++;
        if(i<top) x=gety(s[i],s[i+1]);
        g[0].mat[1][2]=g[0].mat[1][3]=g[0].mat[2][3]=0;
        g[0].mat[2][2]=g[0].mat[3][2]=g[0].mat[3][3]=1;
        g[0].mat[1][1]=1-s[i].k,g[0].mat[2][1]=s[i].k*v,g[0].mat[3][1]=s[i].b;
        for(int j=1;j<=35;j++) g[j]=g[j-1]*g[j-1];
        for(int j=35;j>=0;j--){
            ll np=now+(1ll<<j);
            if(np>=t) continue;
            if(i==top||ck(x-np*v+(f*g[j]).mat[1][1])>=0){
                f=f*g[j];
                now=np;
            }
        }
        f=f*g[0];
        now++;
        if(now==t) break;
    }
    cout<<fixed<<setprecision(10)<<f.mat[1][1];
    return 0;
}