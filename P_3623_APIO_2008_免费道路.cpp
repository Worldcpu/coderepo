#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int u,v,w;
}e[MN],ans[MN];
int n,m,etot,atot,K;
int pre[MN];

bool cmp1(Edge x,Edge y){
    return x.w<y.w;
}

bool cmp2(Edge x,Edge y){
    return x.w>y.w;
}

int root(int x){
    if(pre[x]==x) return pre[x];
    return pre[x]=root(pre[x]);
}

bool merge(int x,int y){
    int rx=root(x),ry=root(y);
    if(rx==ry) return 0;
    pre[ry]=rx;
    return 1;
}

void init(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
    }
}

bool check(){
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(root(i)!=root(j)){
                cout<<"no solution";
                exit(0);
            }
        }
    }
}

int main(){
    init();
    cin>>n>>m>>K;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    sort(e+1,e+1+m,cmp2);
    for(int i=1;i<=m;i++){
        if(merge(e[i].u,e[i].v)&&e[i].w==0){
            etot++;
            e[i].w=-1;
        }
    }
    if(etot>K){
        cout<<"no solution";
        return 0;
    }
    sort(e+1,e+1+m,cmp1);
    init();
    etot=0;
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru==rv) continue;
        if(etot<K||e[i].w==1){
            ans[++atot]=e[i];
            pre[rv]=ru;
            if(e[i].w<1){
                etot++;
                e[i].w=0;
            }
        }
    }
    if(etot<K){
        cout<<"no solution";
        return 0;
    }
    for(int i=1;i<=atot;i++){
        cout<<ans[i].u<<" "<<ans[i].v<<" "<<(ans[i].w==-1?0:ans[i].w)<<'\n';
    }
    
    return 0;
}