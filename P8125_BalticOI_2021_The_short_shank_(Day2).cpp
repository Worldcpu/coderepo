#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,d,T,top,ans,st[MN],lst[MN],t[MN],dtot;
vector<int> adj[MN];
priority_queue<int> q;

namespace Tree{
    int fa[MN],dep[MN],mxdep[MN],hson[MN],htop[MN],len[MN];

    void dfs1(int u,int pre){
        dep[u]=mxdep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            if(mxdep[u]<mxdep[v]) mxdep[u]=mxdep[v],hson[u]=v;
        }
        len[u]=mxdep[u]-dep[u]+1;
    }
    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]){q.push(len[htop[u]]);return;}
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

}using namespace Tree;

int main(){
    cin>>n>>d>>T;
    for(int i=1;i<=n;i++){
        cin>>t[i];
    }
    for(int i=1;i<=n;i++){
        if(t[i]>T){
            while(top&&t[st[top]]+i-st[top]>T) top--;
            if(top) lst[i]=st[top];
        }else{
            while(top&&t[st[top]]+i-st[top]>=t[i]) top--;
            st[++top]=i;
        }
    }
    top=0;
    for(int i=n;i>=1;i--){
        if(!lst[i]) continue;
        while(top&&lst[st[top]]>lst[i]) top--;
        if(top) adj[st[top]].push_back(i),fa[i]=st[top];
        st[++top]=i;
    }
    for(int i=1;i<=n;i++){
        if(t[i]<=T) continue;
        if(!lst[i]) ++ans;
        else if(!fa[i]){
            dfs1(i,0);
            dfs2(i,i);
        }
    }
    while(!q.empty()&&d){
        ans+=q.top();
        q.pop();
        d--;
    }
    cout<<n-ans;

    return 0;
}
