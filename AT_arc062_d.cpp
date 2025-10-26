#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7;
int n,m,K,ans;
set<int> dcc[MN];
vector<int> adj[MN];

namespace Polya{
    int pw[MN],inv[MN];

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
        for(int i=MN-2;i>=0;i--){
            inv[i]=inv[i+1]*(i+1)%MOD;
        }
    }

    int getC(int a,int b){
        if(a<b||a<0||b<0) return 0;
        return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
    }

    int polya(int x){
        int ret=0;
        for(int i=1;i<=x;i++){
            ret=(ret+ksm(K,__gcd(i,x)))%MOD;
        }
        return ret*ksm(x,MOD-2)%MOD;
    }

}

namespace Tarjan{
    int low[MN],dfn[MN],dtot,vdcc,st[MN],top;

    void tarjan(int u,int pre){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]>=dfn[u]){
                    vdcc++;
                    int p,m=0;
                    do{
                        p=st[top--];
                        dcc[vdcc].insert(p);
                    }while(p!=v);
                    dcc[vdcc].insert(u);
                    for(auto p:dcc[vdcc]){
                        for(auto v:adj[p]){
                            if(dcc[vdcc].count(v)) m++;
                        }
                    }
                    m>>=1;
                    if(m<dcc[vdcc].size()){
                        ans=ans*K%MOD;
                    }else if(m==dcc[vdcc].size()){
                        ans=ans*Polya::polya(dcc[vdcc].size())%MOD;
                    }else{
                        ans=ans*Polya::getC(m+K-1,K-1)%MOD;
                    }
                }
            }else{
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(pre==u) top--;
    }


}using namespace Tarjan;


signed main(){
    cin>>n>>m>>K;
    Polya::initpw();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ans=1;
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            top=0;
            tarjan(i,i);
        }
    }
    cout<<ans;
    return 0;
}