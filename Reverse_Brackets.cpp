#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
constexpr int MN=5e4+15,MOD=998244353;
int n,st[MN],top,dtot,pw[MN],inv[MN],ans=1;
mt19937 mt(random_device{}());
vector<int> adj[MN];

namespace THash{
    ull hsh[MN];
    ull Val=mt(),C=mt();
    unordered_map<ull,int> mp;

    ull gethsh(ull x){
        x^=Val;
        x^=(x>>5);
        x^=(x<<3);
        x^=(x>>9);
        x^=(x<<3);
        return x+1145141237ull;
    }

    void dfs(int u,int pre){
        hsh[u]=0;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);
            hsh[u]+=gethsh(hsh[v]);
        }
        hsh[u]+=C;

        mp.clear();
        for(auto v:adj[u]){
            mp[gethsh(hsh[v])]++;
        }

        ans=(ans*pw[adj[u].size()])%MOD;
        for(auto p:mp){
            ans=(ans*inv[p.second])%MOD;
        }
    }
     
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

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

signed main(){
    initpw();
    cin>>n;
    st[++top]=0;
    for(int i=1;i<=n;i++){
        char x;
        cin>>x;
        if(x=='('){
            st[++top]=++dtot;
        }else{
            int now=st[top--];
            adj[st[top]].push_back(now);
        }
    }
    THash::dfs(0,-1);
    cout<<ans;
    return 0;
}