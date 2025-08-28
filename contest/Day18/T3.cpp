#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],m,dg[MN],ans[MN];
vector<int> adj[MN];

struct Node{
    int ans;
    vector<pir> vct;

    friend Node operator+(const Node &x,const Node &y){
        Node ret;
        ret.ans=max(x.ans,y.ans);
        for(auto a:x.vct){
            for(auto b:y.vct){
                if(a.second!=b.second){
                    ret.ans=max(ret.ans,a.first&b.first);
                }
            }
        }
        ret.vct.resize(x.vct.size()+y.vct.size());
        merge(x.vct.begin(),x.vct.end(),y.vct.begin(),y.vct.end(),ret.vct.begin());
        ret.vct.erase(unique(ret.vct.begin(),ret.vct.end()),ret.vct.end());
        auto it=upper_bound(ret.vct.begin(),ret.vct.end(),pir(ret.ans,1000000));
        ret.vct.erase(ret.vct.begin(),it);
        return ret;
    }   

}f[MN];

void toposort(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(!dg[i]){
            q.push(i);
            f[i].ans=-1;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            f[v]=f[v]+f[u];
            dg[v]--;
            if(!dg[v]) q.push(v);
        }
    }
}

signed main(){
    freopen("stone.in","r",stdin);
    freopen("stone.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[i].ans=0;
        f[i].vct.push_back(pir(a[i],i));
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        dg[u]++;
        adj[v].push_back(u);
    }
    toposort();
    for(int i=1;i<=n;i++){
        cout<<f[i].ans<<' ';
    }
    return 0;
}