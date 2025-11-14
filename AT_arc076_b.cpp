#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Node{
    int x,y,id;
}a[MN];
struct Edge{
    int u,v,w;
}e[MN];
int n,etot;

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

    bool cmpe(Edge x,Edge y){
        return x.w<y.w;
    }

    int kru(){
        int ret=0;
        initpre();
        sort(e+1,e+1+etot,cmpe);
        for(int i=1;i<=etot;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru==rv) continue;
            ret+=e[i].w;
            pre[ru]=rv;
        }
        return ret;
    }

}

bool cmpx(Node x,Node y){
    return x.x<y.x;
}

bool cmpy(Node x,Node y){
    return x.y<y.y;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmpx);
    for(int i=1;i<n;i++){
        e[++etot]={a[i].id,a[i+1].id,a[i+1].x-a[i].x};
    }
    sort(a+1,a+1+n,cmpy);
    for(int i=1;i<n;i++){
        e[++etot]={a[i].id,a[i+1].id,a[i+1].y-a[i].y};
    }
    cout<<Kruskal::kru()<<'\n';
    return 0;
}