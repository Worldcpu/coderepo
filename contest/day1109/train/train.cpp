#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,a[MN];
vector<int> adj[MN];

namespace DSU{
    int pre[MN];

    void initpre(){
        iota(pre+1,pre+1+n,1);
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

}using namespace DSU;

namespace Rand{
    uint64_t sd;

    uint64_t rnd() {
        sd ^= sd << 13, sd ^= sd >> 7;
        return sd ^= sd << 17;
    }

    uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
}using namespace Rand;

namespace Tree{
    int st[MN],top,T;
    bool flag=0;

    void dfs(int u,int pre){
        st[++top]=u;
        if(u==T){
            flag=1;
            return;
        }
        for(auto v:adj[u]){
            if(v==pre||flag) continue;
            dfs(v,u);
        }
        if(!flag) top--;
    }

}using namespace Tree;

namespace getsubmx{
    struct Node{
        int ans,sum,pre,suf;

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.sum=x.sum+y.sum;
            ret.pre=max(x.pre,x.sum+y.pre);
            ret.suf=max(y.suf,y.sum+x.suf);
            ret.ans=max({x.ans,y.ans,x.suf+y.pre});
            return ret;
        }
    };

    Node solve(int l,int r){
        if(l==r){
            return {a[st[l]],a[st[l]],a[st[l]],a[st[l]]};
        }
        int mid=(l+r)>>1;
        return solve(l,mid)+solve(mid+1,r);
    }
}

int query(int x,int y){
    // if(x==y) return a[x];
    flag=0,top=0,T=y;
    dfs(x,0);
    return getsubmx::solve(1,top).ans;
}

signed main(){
    freopen("train.in","r",stdin);
    freopen("train.out","w",stdout);
    cin>>n>>m>>sd;   
    sd=splitmix64(sd);
    for(int i=1;i<=n;i++){
        a[i]=(uint32_t)rnd();
    }
    initpre();
    while(m--){
        int u=rnd()%n+1,v=rnd()%n+1;
        if(root(u)==root(v)){
            auto ret=query(u,v);
            sd^=ret;
        }else{
            adj[u].push_back(v);
            adj[v].push_back(u);
            pre[root(u)]=root(v);
        }
    }
    cout<<sd;
    return 0;
}