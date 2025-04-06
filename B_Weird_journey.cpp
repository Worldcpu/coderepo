#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int MN=5e6+15;
int n,m,pre[MN],tot,du[MN],bu[MN],bv[MN];


// void hij(int u){
//     for(int &i=cur[i];i<adj[u].size();i++){
//         if(vis[adj[u][i].id])continue;
//         vis[adj[u][i].id]=1;
//         hij(adj[u][i].v);

//     }
// }

int root(int x){
    if(pre[x]==x) return x;
    return pre[x]=root(pre[x]);
}

void merge(int x,int y){
    // if(x==y) return;
    int rx=root(x),ry=root(y);
    pre[rx]=ry;
}

int main(){
    ios::sync_with_stdio(0);
    // int u,v;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        pre[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        bu[i]=u;
        if(u==v) tot++;
        else{
            du[u]++;
            du[v]++;
        }
        merge(u,v);
    }
    
    int pre1=root(bu[1]);
    //cout<<pre1<<" ";
    for(int i=2;i<=m;i++){
        if(root(bu[i])!=pre1){
            cout<<0;
            return 0;
        }
    }

    ull ans=0;
    ans+=(ull)(tot-1)*tot/2;
    ans+=tot*(ull)(m-tot);
    for(int i=1;i<=n;i++){
        ans+=(ull)du[i]*(du[i]-1)/2;
    }
    cout<<ans;
    return 0;
}