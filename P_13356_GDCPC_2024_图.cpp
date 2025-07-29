#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e5+15;
int n,m,K;

struct DSU{
    vector<int> pre;
    vector<vector<int>> adj;
    vector<pir> e;
    int siz[MN];

    void init(int n){
        pre.resize(n+1);
        adj.resize(n+1);
        e.clear();
        for(int i=0;i<=n;i++) pre[i]=i,siz[i]=1;;
    }

    DSU(int n=0){
        if(!n) return;
        init(n);
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    bool issame(int x,int y){
        return root(x)==root(y);
    }

    void merge(int x,int y){
        int rx=root(x),ry=root(y);
        if(rx==ry) return;
        pre[ry]=rx;
        siz[rx]+=siz[ry];
        adj[x].push_back(y);
        adj[y].push_back(x);
        e.push_back(pir(x,y));
    }

    vector<int> getpath(int x,int y,int pree){
        bool flag=0||(x==y);
        vector<int> ans;
        for(auto v:adj[x]){
            if(v==pree) continue;
            auto tmp=getpath(v,y,x);
            if(tmp.size()){
                flag=1;
                ans=tmp;
            }
        }
        if(flag){
            ans.push_back(x);
        }
        return ans;
    }

};

void solve(){
    cin>>n>>m;
    K=(m+n-2)/(n-1);
    vector<DSU> dsu(K);
    vector<pir> edge;
    for(int i=0;i<K;i++){
        dsu[i].init(n);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        edge.push_back(pir(u,v));
    }
    for(auto e:edge){
        int l=0,r=K-1;
        while(l<r){
            int mid=(l+r)>>1;
            if(!dsu[mid].issame(e.first,e.second)) r=mid;
            else l=mid+1;
        }
        if(!dsu[l].issame(e.first,e.second)) dsu[l].merge(e.first, e.second);
    }
    auto p=dsu[K-1].e[0];
    vector<vector<int>> ans={{p.first,p.second}};
    for(int i=0;i<K-1;i++){
        auto ret=dsu[i].getpath(p.first,p.second,0);
        reverse(ret.begin(),ret.end());
        ans.push_back(ret);
    }
    cout<<p.first<<" "<<p.second<<'\n';
    for(auto vct:ans){
        cout<<vct.size()<<' ';
        for(auto qwq:vct) cout<<qwq<<" ";
        cout<<'\n';
    }
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}