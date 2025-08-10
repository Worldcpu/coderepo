#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55,MOD=998244353;
int d[MN],n,x,ans1,ans2,ptot,tot,pos[MN*MN],L[MN],R[MN];

struct Matrix{
    int mat[MN][MN];

    Matrix(int x=0){
        memset(mat,0,sizeof(mat));
        if(x) for(int i=0;i<MN;i++) mat[i][i]=x;
    }

    friend Matrix operator*(const Matrix &x,const Matrix &y){
        Matrix ret;
        for(int i=0;i<MN;i++)
            for(int j=0;j<MN;j++)
                for(int k=0;k<MN;k++)
                    ret.mat[i][j]=(ret.mat[i][j]+x.mat[i][k]*y.mat[k][j]%MOD)%MOD;
        return ret;
    }
}A,B;

Matrix ksm(Matrix a,int b){
    Matrix ret(1);
    while(b){
        if(b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

int solve(int l,int r,int sum){
    A=Matrix(); A.mat[0][0]=1;
    tot=ptot=0;
    int ret=0;
    for(int i=l,summ=sum;i<=r;summ+=d[i],i++){
        L[++tot]=(d[i]>0)?summ+1:summ-1;
        R[tot]=summ+d[i];
        if(tot==1) L[1]=sum;
        pos[++ptot]=L[tot];
        pos[++ptot]=L[tot]+1;
        pos[++ptot]=L[tot]-1;
        pos[++ptot]=R[tot];
        pos[++ptot]=R[tot]+1;
        pos[++ptot]=R[tot]-1;
    }
    sort(pos+1,pos+1+ptot);
    ptot=unique(pos+1,pos+1+ptot)-pos-1;
    for(int i=1,lst=sum-1;i<=ptot;i++){
        if(pos[i]<=lst||pos[i]>sum+ans1) continue;
        B=Matrix();
        for(int j=1;j<=tot;j++){
            if(min(L[j],R[j])>lst+1||max(L[j],R[j])<pos[i]) continue;
            for(int k=0;k<=j;k++) B.mat[k][j]=1;
            if(L[j]>=R[j]) B.mat[j][j]=0;
        }
        A=A*ksm(B,pos[i]-lst);
        lst=pos[i];
    }
    for(int i=0;i<=tot;i++) ret=(ret+A.mat[0][i])%MOD;
    return ret;
}

signed main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>d[i];
        if(!d[i]) --n,--i;
    }
    int sum=0;
    for(int i=1;i<=n;sum+=d[i],i++){
        for(int j=i,summ=sum;j<=n;j++){
            summ+=d[j];
            ans1=max(ans1,summ-sum);
        }
    }
    if(!ans1){
        cout<<1<<" "<<(-sum+1+MOD)%MOD;
        return 0;
    }
    sum=0;
    for(int i=1,r;i<=n;sum+=d[i],i++){
        r=0;
        for(int j=i,summ=sum;j<=n;j++){
            summ+=d[j];
            if(summ-sum==ans1) r=j;
        }
        if(r>0){
            ans2=(ans2+solve(i,r,sum))%MOD;
            i=r;
        }
    }
    cout<<ans1+1<<" "<<ans2;
    return 0;
}
