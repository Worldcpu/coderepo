#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3520,INF=0x3f3f3f3f;
int n,K,q,a[MN],p[MN],pos[MN],sum0[MN],suma[MN],num[MN];

struct Matrix{
    int mat[MN][MN];

    Matrix(){
        memset(mat,0,sizeof(mat));
    }

    friend Matrix operator *(Matrix x,Matrix y){
        Matrix c,ret;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                c.mat[i][j]=i==j?i:0;
                ret.mat[i][j]=i==j?0:INF;
            }
        }
        for(int len=2;len<=n;len++){
            for(int l=1;l+len-1<=n;l++){
                int r=l+len-1;
                ret.mat[l][r]=INF;
                for(int k=c.mat[l][r-1];k<=c.mat[l+1][r];k++){
                    int t=x.mat[l][k]+y.mat[k][r];
                    if(ret.mat[l][r]>t){
                        ret.mat[l][r]=t;
                        c.mat[l][r]=k;
                    }
                }
            }
        }
        return ret;
    }

}A,B,ans[2];

int w1(int l,int r){
    if(l>r) return 0;
    int fl=a[l]==1?pos[l]:pos[l+1],fr=pos[r];
    int mid=(fl+fr)>>1;
    return sum0[num[mid]]*(mid-fl+1)-(suma[num[mid]]-suma[l-1])+(suma[r]-suma[num[mid]])-sum0[num[mid]]*(fr-mid);
}

int w2(int l,int r){
    if(l>r) return 0;
    int fl=a[l]==1?pos[l]:pos[l+1],fr=pos[r];
    int mid=(fl+fr)>>1;
    return sum0[r]*(fr-fl+1)-(suma[r]-suma[l-1]);
}

Matrix solve(){
    int tot=0,k=K/2-1;
    for(int i=1;i<=n;i++){
        sum0[i]=sum0[i-1]+(!a[i]);
        suma[i]=suma[i-1]+sum0[i]*a[i];
        if(a[i]==1){
            pos[i]=++tot;
            num[tot]=i;
        }else pos[i]=pos[i-1];
    }
    if(K==1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                A.mat[i][j]=w2(i,j);
            }
        }
        return A;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            A.mat[i][j]=w1(i,j);
            B.mat[i][j]=w1(i+1,j);
        }
    }
    while(k){
        if(k&1) A=A*B;
        B=B*B;
        k>>=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            B.mat[i][j]=w1(i+1,j);
        }
    }
    if(K&1) A=A*B;
    return A;
}

int main(){
    cin>>n>>K>>q;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a[i]=a[i-1]^x;
    }
    ans[0]=solve();
    for(int i=1;i<=n;i++){
        a[i]^=1;
    }
    ans[1]=solve();
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<ans[a[l-1]].mat[l][r]<<'\n';
    }
    return 0;
}