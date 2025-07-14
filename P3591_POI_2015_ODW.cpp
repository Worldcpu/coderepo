#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e4+15,MB=250;
int n,a[MN],b[MN],c[MN],sum[MN],s[MB+5][MN],fa[32][MN],dep[MN];
vector<int> adj[MN];

void dfs1(int u,int pre){
    dep[u]=dep[pre]+1;
    fa[0][u]=pre;
    sum[u]=sum[pre]+a[u];
    for(int i=1;i<=30;i++){
        fa[i][u]=fa[i-1][fa[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
    }
}

void dfs2(int u,int pre){
    int p=pre;
    for(int i=2;i<=MB;i++){
        p=fa[0][p];
        if(p==0) break;
        s[i][u]=s[i][p]+a[u];
    }
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs2(v,u);
    }
}

int lca(int x,int y){
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    for(int i=30;i>=0;i--){
        if(fa[i][y]&&dep[fa[i][y]]>=dep[x]) y=fa[i][y];
    }
    if(x==y) return x;
    for(int i=30;i>=0;i--){
        if(fa[i][x]!=fa[i][y]){
            x=fa[i][x],y=fa[i][y];
        }
    }
    return fa[0][x];
}

int getfa(int x,int k){
    for(int i=30;i>=0;i--){
        if((k>>i)&1) x=fa[i][x];
    }
    return x;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<n;i++) cin>>c[i];
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<n;i++){
        int u=b[i],v=b[i+1],k=c[i];
        int lcaa=lca(u,v);
        if(k==1){
            cout<<sum[u]+sum[v]-sum[lcaa]-sum[fa[0][lcaa]]<<'\n';
        }
        else if(k<=MB){
            int ans=s[k][u],dis=(dep[u]-dep[lcaa])%k;
            if(dis==0) dis=k;
            for(int i=30;i>=0;i--){
                if(fa[i][u]&&dep[fa[i][u]]-dep[lcaa]>=dis) u=fa[i][u];
            }
            ans+=a[u]-s[k][u];
            if(dep[u]+dep[v]-(dep[lcaa]<<1)>=k){
                dis=k-dep[u]+dep[lcaa];
                u=v;
                for(int i=30;i>=0;i--){
                    if(fa[i][u]&&dep[fa[i][u]]-dep[lcaa]>=dis) u=fa[i][u];
                }
                dis=(dep[v]-dep[u])%k;
                if(dis!=0) ans+=a[v];
                v=getfa(v,dis);
                ans+=s[k][v]-s[k][u]+a[u];
            }else ans+=a[v];
            cout<<ans<<'\n';
        }else{
            int ans=0;
            while(dep[u]-dep[lcaa]>k){
                ans+=a[u];
                u=getfa(u,k);
            }
            ans+=a[u];
            if(dep[u]+dep[v]-(dep[lcaa]<<1)>=k){
                int dis=k-dep[u]+dep[lcaa];
                u=v;
                for(int i=30;i>=0;i--){
                    if(fa[i][u]&&dep[fa[i][u]]-dep[lcaa]>=dis) u=fa[i][u];
                }
                dis=(dep[v]-dep[u])%k;
                if(dis!=0) ans+=a[v];
                v=getfa(v,dis);
                while(dep[v]-dep[u]>=k){
                    ans+=a[v];
                    v=getfa(v,k);
                }
                ans+=a[v];
            }else ans+=a[v];
            cout<<ans<<'\n';
        }
    }
    return 0;
}
