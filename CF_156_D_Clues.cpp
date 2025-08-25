#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int pre[MN],n,m,K,cnt[MN],MOD,ans=1;

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpre(){
    for(int i=1;i<MN;i++){
        pre[i]=i;
    }
}

signed main(){
    initpre();
    cin>>n>>m>>MOD;
    if(MOD==1){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        pre[root(v)]=root(u);
    }
    for(int i=1;i<=n;i++){
        cnt[root(i)]++;
    }
    for(int i=1;i<=n;i++){
        if(pre[i]==i){
            K++;
            ans=ans*cnt[i]%MOD;
        }
    }
    if(K==1){
        cout<<1;
        return 0;
    }
    cout<<ans*ksm(n,K-2)%MOD;

    return 0;
}