#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=6,MOD=998244353;
struct Edge{
    int u,v;
}e[MN];
int n,sum,invs,ans;
bool del[MN];
unordered_map<int,int> mp;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void dfs(int stp,int p){
    bool flag=1;
    for(int i=1;i<n;i++){
        if(del[e[i].u]||del[e[i].v]) continue;
        flag=0;
        break;
    }
    if(flag){
        ans=(ans+p*stp%MOD)%MOD;
        return;
    }
    int sumd=0;
    for(int i=1;i<=n;i++){
        sumd+=(!del[i]);
    }
    for(int i=1;i<=n;i++){
        if(!del[i]){
            del[i]=1;
            dfs(stp+1,p*ksm(sumd,MOD-2)%MOD);
            del[i]=0;
        }
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        e[i]={u,v};
    }
    dfs(0,1);
    cout<<ans;
    cerr<<invs;
    return 0;
}