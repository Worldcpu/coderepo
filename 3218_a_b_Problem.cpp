#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int n,a[MN],b[MN],L[MN],R[MN],p[MN],btot,ans;

namespace Dinic{
    struct Edge{
        int v,w,id;
    };
    int S,T,cur[MN],dep[MN];
    vector<Edge> adj[MN];

    void add(int u,int v,int w){
        int us=adj[u].size(),vs=adj[v].size();
        adj[u].push_back({v,w,vs});
        adj[v].push_back({u,0,us});
    }

    bool bfs(int S,int T){
        memset(dep,-1,sizeof(dep));
        queue<int> q;
        dep[S]=0;
        q.push(S);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto &e:adj[u]){
                if(dep[e.v]==-1&&e.w>0){
                    dep[e.v]=dep[u]+1;
                    q.push(e.v);
                }
            }
        }
        memset(cur,0,sizeof(cur));
        return (dep[T]!=-1);
    }

    int dfs(int u,int lim,int T){
        if(u==T) return lim;
        for(int &i=cur[u];i<(int)adj[u].size();i++){
            int v=adj[u][i].v;
            if(dep[v]==dep[u]+1 && adj[u][i].w>0){
                int p=dfs(v,min(lim,adj[u][i].w),T);
                if(p){
                    adj[u][i].w-=p;
                    adj[v][adj[u][i].id].w+=p;
                    return p;
                }else dep[v]=-1;
            }
        }
        return 0;
    }

    int dinic(int S,int T){
        int ans=0,flow;
        while(bfs(S,T)){
            while( (flow=dfs(S,INF,T)) ){
                ans+=flow;
            }
        }
        return ans;
    }
}using namespace Dinic;

namespace ZXT{
    #define ls(p) (t[p].lson)
    #define rs(p) (t[p].rson)
    int lson[MN],rson[MN],rt[MN],tot;

    void insert(int &p,int lst,int l,int r,int x){
        p=++tot;
        lson[p]=lson[lst],rson[p]=rson[lst];
        if(l==r){
            if(lst){
                add(p+T,lst+T,INF);
            }
            add(p+T,x,INF);
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=a[x]) insert(lson[p],lson[lst],l,mid,x);
        else insert(rson[p],rson[lst],mid+1,r,x);
        if(lson[p]) add(p+T,lson[p]+T,INF);
        if(rson[p]) add(p+T,rson[p]+T,INF);
    }

    void query(int p,int l,int r,int fl,int fr,int x){
        if(!p) return;
        if(l>fr||r<fl) return;
        if(l>=fl&&r<=fr){
            add(x+n,p+T,INF);
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=fl) query(lson[p],l,mid,fl,fr,x);
        if(mid<fr) query(rson[p],mid+1,r,fl,fr,x);
    }

}using namespace ZXT;

signed main(){
    cin>>n;
    S=0,T=2*n+1;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>a[i]>>x>>y>>L[i]>>R[i]>>p[i];
        ans+=x+y;
        b[++btot]=a[i];
        b[++btot]=L[i];
        b[++btot]=R[i];
        add(S,i,x);
        add(i,T,y);
        add(i,i+n,p[i]);
    }
    sort(b+1,b+1+btot);
    btot=unique(b+1,b+1+btot)-b-1;
    for(int i=1;i<=n;i++){
        L[i]=lower_bound(b+1,b+1+btot,L[i])-b;
        R[i]=lower_bound(b+1,b+1+btot,R[i])-b;
        a[i]=lower_bound(b+1,b+1+btot,a[i])-b;
        if(i>1) ZXT::query(rt[i-1],1,btot,L[i],R[i],i);
        ZXT::insert(rt[i],rt[i-1],1,btot,i);
    }
    cout<<ans-dinic(S,T);
    return 0;
}