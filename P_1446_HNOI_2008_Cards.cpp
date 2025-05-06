#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int sr,sb,sg,n,m,tot,P,f[MN][MN][MN];
int a[MN],siz[MN];
bool vis[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=(ret*a)%P;
        a=(a*a)%P;
        b>>=1;
    }
    return ret;
}

void getring(){
    memset(vis,0,sizeof(vis));
    tot=0;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int p=i,len=0;
            while(!vis[p]){
                len++;
                vis[p]=1;
                p=a[p];
            }
            siz[++tot]=len;
        }
    }
}

int clac(){
    memset(f,0,sizeof(f));
    f[0][0][0]=1;
    for(int i=1;i<=tot;i++){
        for(int j=sr;j>=0;j--){
            for(int k=sb;k>=0;k--){
                for(int p=sg;p>=0;p--){
                    if(j>=siz[i]){
                        f[j][k][p]=(f[j-siz[i]][k][p]+f[j][k][p])%P;
                    }
                    if(k>=siz[i]){
                        f[j][k][p]=(f[j][k-siz[i]][p]+f[j][k][p])%P;
                    }
                    if(p>=siz[i]){
                        f[j][k][p]=(f[j][k][p-siz[i]]+f[j][k][p])%P;
                    }
                }
            }
        }
    }
    return f[sr][sb][sg];
}

signed main(){
    int ans=0;
    cin>>sr>>sb>>sg>>m>>P;
    n=sr+sb+sg;
    for(int i=1;i<=n;i++){
        a[i]=i;
    }
    getring();

    // for(int i=1;i<=tot;i++){
    //     cout<<siz[i]<<" ";
    // }
    ans=(ans+clac())%P;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>a[j];
        }
        getring();
        ans=(ans+clac())%P;
    }
    cout<<ans*ksm(m+1,P-2)%P;
    return 0;
}