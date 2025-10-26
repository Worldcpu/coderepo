#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,m,K;
vector<int> adj[MN];
vector<int> ans;

namespace Tree{
    int col[MN];
    
    void dfs(int u,int pre,int color){
        col[u]=color;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u,color^1);
        }
    }

    void solve(){
        cout<<1<<'\n';
        dfs(1,0,1);
        int cnt=0;
        for(int i=1;i<=n&&cnt<(K+1)/2;i++){
            if(col[i]==1){
                cnt++;
                ans.push_back(i);
            }
        }
            if(ans.size()!=(K+1)/2){
                ans.clear();
                cnt=0;
                for(int i=1;i<=n&&cnt<(K+1)/2;i++){
                    if(!col[i]){
                        cout<<i<<' ';
                        cnt++;
                    }
                }
            }else for(auto p:ans) cout<<p<<' ';
    }
}

namespace YB{
    int col[MN],fa[MN],dep[MN];
    bool vis[MN],flag;
    pir st;

    void dfs1(int u,int pre){
        vis[u]=1;
        dep[u]=dep[pre]+1;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            if(vis[v]){
                if(dep[v]<dep[u]&&dep[u]-dep[v]+1<=K){
                    flag=1;
                    st=pir(u,v);
                }
            }else dfs1(v,u);
        }
    }

    void dfs2(int u,int pre,int color){
        col[u]=color;
        if(dep[u]>K) return;
        for(auto v:adj[u]){
            if(v==pre||fa[v]!=u) continue;
            dfs2(v,u,color^1);
        }
    }

}using namespace YB;


signed main(){
    cin>>n>>m>>K;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if(m==n-1){
        Tree::solve();
    }else{
        dfs1(1,0);
        if(flag){
            cout<<"2\n";
            int it;
            for(it=st.first;it!=st.second;it=fa[it]){
                ans.push_back(it);
            }
            ans.push_back(it);
            cout<<ans.size()<<'\n';
            for(auto p:ans) cout<<p<<' ';
        }else{
            dfs2(1,0,1);
            cout<<"1\n";
            int cnt=0;
            for(int i=1;i<=n&&cnt<(K+1)/2;i++){
                if(col[i]){
                    ans.push_back(i);
                    cnt++;
                }
            }
            if(ans.size()!=(K+1)/2){
                ans.clear();
                cnt=0;
                for(int i=1;i<=n&&cnt<(K+1)/2;i++){
                    if(!col[i]){
                        cout<<i<<' ';
                        cnt++;
                    }
                }
            }else for(auto p:ans) cout<<p<<' ';
        }
    }

    return 0;
}