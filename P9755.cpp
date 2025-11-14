#include<bits/stdc++.h>
#define int long long
#define lint __int128
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],b[MN],c[MN],zero[MN];
vector<int> adj[MN];

namespace Check{
    int lim[MN],seq[MN],tot,dg[MN],parent[MN];

    void dfs1(int u,int pre){
        parent[u]=pre;
        dg[u]=0;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            dg[u]++;
        }
    }

    void worklim(int x,int res){
        int l=1,r=n,ret=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            lint sum=0,one=1;
            if(c[x]>=0){
                sum = one*(res-mid+1)*b[x]
                    + one*(mid+res)*(res-mid+1)/2*c[x];
            }else{
                if(mid>zero[x]){
                    sum = res-mid+1;
                }else if(res>zero[x]){
                    sum = one*(zero[x]-mid+1)*b[x]
                        + one*(mid+zero[x])*(zero[x]-mid+1)/2*c[x]
                        + (res - zero[x]);
                }else{
                    sum = one*(res-mid+1)*b[x]
                        + one*(mid+res)*(res-mid+1)/2*c[x];
                }
            }
            if(sum >= (lint)a[x]) ret=mid,l=mid+1;
            else r=mid-1;
        }       
        lim[x]=ret;
    }

    void toposort(){
        priority_queue<pir> q;
        for(int i=1;i<=n;i++){
            if(!dg[i]){
                q.push(pir(lim[i],i));
            }
        }
        for(int T=n; T>0; T--){
            if(q.empty()) break;
            int u=q.top().second;
            q.pop();
            seq[T]=u;
            int p=parent[u];
            if(p){
                if(--dg[p]==0){
                    q.push(pir(lim[p],p));
                }
            }
        }
        tot=0;
        for(int i=1;i<=n;i++) if(seq[i]) tot++;
    }
}

bool check(int mid){
    for(int i=1;i<=n;i++){
        Check::dg[i]=0;
        Check::lim[i]=0;
        Check::seq[i]=0;
        Check::parent[i]=0;
    }
    Check::dfs1(1,0);
    for(int i=1;i<=n;i++){
        Check::worklim(i,mid);
        if(Check::lim[i]<0) return 0;
    }
    Check::toposort();
    if(Check::tot!=n) return 0;
    for(int i=1;i<=n;i++){
        if(i>Check::lim[Check::seq[i]]){
            return 0;
        }
    }
    return 1;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i]>>c[i];
        if(c[i]<0){
            zero[i]=(1-b[i])/c[i];
        }
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int l=1,r=1e9,ret=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ret=mid;
        else l=mid+1;
    }
    cout<<ret;
    return 0;
}