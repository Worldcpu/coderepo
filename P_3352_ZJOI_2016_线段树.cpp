#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=1e9+7,INV2=500000004;
struct Node{
    int v,id;
}a[MN];
int n,q,ans[MN],f[MN][MN],s1[MN][MN],s2[MN][MN],v[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int w(int l,int r){
    return (l*(l+1)%MOD+(n-r+1)*(n-r+2)%MOD+(r-l-1)*(r-l)%MOD)*INV2%MOD;
}

bool cmp(Node x,Node y){
    return x.v<y.v;
}

signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i].v;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    v[n+1]=1;
    for(int i=n;i>=1;i--){
        int lst=0;
        v[a[i].id]=1;
        for(int j=1;j<=n+1;j++){
            if(v[j]){
                f[lst][j]+=a[i].v-a[i-1].v;
                lst=j;
            }
        }
    }
    ans[1]=a[n].v*ksm(n*(n+1)%MOD*INV2%MOD,q);
    for(int i=2;i<=n;i++) ans[i]=ans[1];
    for(int i=1;i<=q;i++){
        for(int j=0;j<=n;j++){
            for(int k=n+1;k>j+1;k--){
                if(j){
                    s1[j][k]=(s1[j-1][k]+f[j][k]*j%MOD)%MOD;
                }else s1[j][k]=f[j][k]*j%MOD;
                if(k<=n){
                    s2[j][k]=(s2[j][k+1]+f[j][k]*(n-k+1)%MOD)%MOD;
                }else s2[j][k]=(f[j][k]*(n-k+1)%MOD)%MOD;
            }
        }
        for(int j=0;j<=n;j++){
            for(int k=j+2;k<=n+1;k++){
                f[j][k]=f[j][k]*w(j,k)%MOD;
                if(j){
                    f[j][k]=(f[j][k]+s1[j-1][k])%MOD;
                }
                if(k<=n) f[j][k]=(f[j][k]+s2[j][k+1])%MOD;
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=i+2;j<=n+1;j++){
            for(int k=i+1;k<j;k++){
                ans[k]=(ans[k]-f[i][j]+MOD)%MOD;
            }
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    return 0;
}