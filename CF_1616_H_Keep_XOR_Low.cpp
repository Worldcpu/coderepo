#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353;
int n,X,pw[MN],a[MN],ch[MN][2],siz[MN],tot=1;

void insert(int x){
    int u=1;
    siz[u]++;
    for(int i=30;i>=0;i--){
        bool p=(x>>i)&1;
        if(!ch[u][p]) ch[u][p]=++tot;
        u=ch[u][p];
        siz[u]++;
    }
}

int dfs(int x,int y,int K){
    if(!x) return pw[siz[y]];
    if(!y) return pw[siz[x]];
    if(x==y){
        if(K<0) return pw[siz[x]];
        int ls=ch[x][0],rs=ch[x][1];
        if((X>>K)&1) return dfs(ls,rs,K-1);
        else return (dfs(ls,ls,K-1)+dfs(rs,rs,K-1)-1+MOD)%MOD;
    }
    else{
        if(K<0) return pw[siz[x]+siz[y]];
        int lsx=ch[x][0],rsx=ch[x][1],lsy=ch[y][0],rsy=ch[y][1];
        if((X>>K)&1) return dfs(lsx,rsy,K-1)*dfs(rsx,lsy,K-1)%MOD;
        else{
            int ret=(dfs(lsx,lsy,K-1)+dfs(rsx,rsy,K-1)-1+MOD)%MOD;
            ret=(ret+(pw[siz[lsx]]-1+MOD)*(pw[siz[rsx]]-1+MOD)%MOD)%MOD;
            ret=(ret+(pw[siz[lsy]]-1+MOD)*(pw[siz[rsy]]-1+MOD)%MOD)%MOD;
            return ret;
        }
    }
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*2%MOD;
}

signed main(){
    init();
    cin>>n>>X;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        insert(x);
    }
    cout<<(dfs(1,1,30)-1+MOD)%MOD;
    return 0;
}
