#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int u,v,w;
}e[MN];
int n,m;

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

namespace Kruskal{

    bool cmp(Edge x,Edge y){
        return x.w<y.w;
    }

    int kru(){
        initpre();
        int ret=0;
        sort(e+1,e+1+m,cmp);
        for(int i=1;i<=m;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru==rv) continue;
            pre[ru]=rv;
            ret+=e[i].w;
        }
        return ret;
    }

}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    cout<<Kruskal::kru()<<'\n';
    return 0;
}