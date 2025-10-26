#include<bits/stdc++.h>
using namespace std;
constexpr int MN=50;
struct Edge{
    int u,v;
}e[MN];
int n,m,ans=1e9;
bool vis[MN];


int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v;
    }
    for(int s=1;s<(1<<n);s++){
        int ret=0;
        for(int i=1;i<=m;i++){
            int colu=(s>>e[i].u-1)&1,colv=(s>>e[i].v-1)&1;
            if(!(colu^colv)) ret++;
        }
        ans=min(ans,ret);
    }
    cout<<ans;

    return 0;
}