#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MS=(1<<18)+15,MN=1e5+15,ML=30,MOD=1e9+1;
int n,ans=1,limh,ln[ML],lim[ML],a[ML][ML],f[ML][MS];
bool vis[MN];
bool isok[MS];

void init(int x){
    for(int i=1;i<=11;i++){
        if(i==1) a[i][1]=x;
        else a[i][1]=a[i-1][1]*3;
        if(a[i][1]>n) break;
        limh=i;
        ln[i]=1;
        vis[a[i][1]]=1;
        for(int j=2;j<=28;j++){
            a[i][j]=a[i][j-1]*2;
            if(a[i][j]>n) break;
            ln[i]=j;
            vis[a[i][j]]=1;
        }
        lim[i]=(1<<ln[i])-1;
    }

}

int solve(int x){
    for(int i=0;i<=lim[1];i++) f[1][i]=isok[i];
    for(int i=2;i<=limh;i++){
        for(int j=0;j<=lim[i];j++){
            if(!isok[j]) continue;
            f[i][j]=0;
            for(int k=0;k<=lim[i-1];k++){
                if(isok[k]&&((k&j)==0)) (f[i][j]+=f[i-1][k])%=MOD;
            }
        }
    }
    int ret=0;
    for(int i=0;i<=lim[limh];i++){
        (ret+=f[limh][i])%=MOD;
    }
    return ret;
}

signed main(){
    cin>>n;
    for(int i=0;i<(1<<18);i++){
        isok[i]=((i<<1)&i?0:1);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            init(i);
            ans=ans*solve(i)%MOD;           
        }
    }
    cout<<ans;

    return 0;
}