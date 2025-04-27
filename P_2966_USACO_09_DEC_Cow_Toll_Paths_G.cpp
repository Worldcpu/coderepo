#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
struct Node{
    int k,pos;
};
int n,m,q;
Node c[MN];
int mp[MN][MN],ans[MN][MN];

bool cmp(Node x,Node y){
    return x.k<y.k;
}

signed main(){
    memset(mp,0x3f,sizeof(mp));
    memset(ans,0x3f,sizeof(ans));
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        mp[i][i]=0;
        cin>>c[i].k;
        c[i].pos=i;
    }
    sort(c+1,c+1+n,cmp);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        mp[u][v]=min(mp[u][v],w);
        mp[v][u]=min(mp[v][u],w);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(mp[c[i].pos][c[j].pos]){
                    mp[c[i].pos][c[j].pos]=min(mp[c[i].pos][c[j].pos],mp[c[i].pos][c[k].pos]+mp[c[k].pos][c[j].pos]);
                    ans[c[i].pos][c[j].pos]=min(ans[c[i].pos][c[j].pos],mp[c[i].pos][c[k].pos]+mp[c[k].pos][c[j].pos]+max({c[i].k,c[j].k,c[k].k}));
                }
            }
        }
    }
    while(q--){
        int u,v;
        cin>>u>>v;
        cout<<ans[u][v]<<'\n';
    }
    return 0;
}