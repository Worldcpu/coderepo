#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15,ML=30,MK=2.5e4+15;
int n,r,q,ccnt[MN],fid[MN],id[MN],cf[MN],MB;
int ans[520][MK];
vector<int> adj[MN],col[MN],dcol[MN];

namespace Tree{
    int dfn[MN],siz[MN],dtot;

    void dfs(int u,int pre){
        dfn[u]=++dtot;
        siz[u]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);
            siz[u]+=siz[v];
        }
    }

    int cmpdfn(int x,int y){
        return dfn[x]<dfn[y];
    }
}using namespace Tree;

bool cmp(int x,int y){
    return ccnt[x]>ccnt[y];
}

signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>r>>q;
    MB=sqrt(n*__lg(n)*2);
    for(int i=1;i<=n;i++){
        int fa,color;
        if(i!=1){
            cin>>fa;
            adj[fa].push_back(i);
        }
        cin>>color;
        col[color].push_back(i);
        ccnt[color]++;
    }
    for(int i=1;i<=r;i++) id[i]=i;
    sort(id+1,id+1+r,cmp);
    dfs(1,0);
    for(int i=1;i<=r;i++){
        fid[id[i]]=i;
        for(auto p:col[i]) dcol[i].push_back(dfn[p]);
        sort(dcol[i].begin(),dcol[i].end());
    }
    for(int i=1;i<=r&&ccnt[id[i]]>=MB;i++){
        for(int i=1;i<=n+1;i++) cf[i]=0;
        for(auto p:col[id[i]]){
            cf[dfn[p]]++;
            cf[dfn[p]+siz[p]]--;
        }
        for(int i=1;i<=n+1;i++){
            cf[i]+=cf[i-1];
        }
        for(int j=1;j<=r;j++){
            for(auto p:col[j]){
                ans[i][j]+=cf[dfn[p]];
            }
        }
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        if(ccnt[x]<MB){
            long long ret=0;
            for(auto p:col[x]){
                ret+=upper_bound(dcol[y].begin(),dcol[y].end(),dfn[p]+siz[p]-1)-lower_bound(dcol[y].begin(),dcol[y].end(),dfn[p]);
            }
            cout<<ret<<endl;
        }else cout<<ans[fid[x]][y]<<endl;
    }
    
    return 0;
}
