#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Node{
    int u,v,w;
}e[MN];
int pre[MN],n,a[MN],m;

void initpre(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
    }
}

bool cmp(Node x,Node y){
    return x.w>y.w;
}

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

bool issame(int x,int y){
    int rx=root(x),ry=root(y);
    if(rx==ry) return 1;
    return 0;
}

int main(){
    initpre();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    sort(e+1,e+1+m,cmp);
    for(int i=1;i<=m+1;i++){
        if(issame(e[i].u,e[i].v)){
            cout<<e[i].w<<'\n';
            break;
        }else{
            if(!a[e[i].u]){
                a[e[i].u]=e[i].v;
            }else pre[root(a[e[i].u])]=root(e[i].v);
            if(!a[e[i].v]){
                a[e[i].v]=e[i].u;
            }else pre[root(a[e[i].v])]=root(e[i].u);
        }
    }
    return 0;
}