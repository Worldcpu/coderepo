#include<bits/stdc++.h>
using namespace std;
constexpr int MV=3e5+15,MN=3e5+15;
struct Edge{
    int v,id;
};
int n,etot;
bool visqwq[MN];
vector<int> prime;
vector<Edge> adj[MN];
vector<bool> visp(MV,0);

namespace Euler{
    int cur[MN];
    bool vis[MN];
    vector<int> st;

    void dfs(int u){
    while (cur[u] < (int)adj[u].size()) {
        Edge e = adj[u][cur[u]++];
        if (!vis[e.id]) {
            vis[e.id] = 1;
            dfs(e.v);
        }
    }

            st.push_back(u);
    }
}using namespace Euler;

void initpri(int n){
    visp[1]=1;
    for(int i=2;i<=n;i++){
        if(!visp[i]){
            prime.push_back(i);
            visp[i]=1;
        }
        for(auto p:prime){
            if(1ll*i*p>n) break; 
            visp[i*p]=1;
            if(i%p==0){
                break;
            }
        }
    }
}

int check(int x){
    if(x&1) return x*(x+1)/2+1;
    else return x*(x+1)/2-x/2+2;
}

void init(int n){
    for(int i=0;i<=n;i++){
        adj[i].clear();
        cur[i]=0;
    }
    for(int i=1;i<=etot;i++){
        vis[i]=0;
    }
    etot=0;
    st.clear();
}

void solve(){
    cin>>n;
    int l=1,r=1e4,ret=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)>=n) r=mid-1,ret=mid;
        else l=mid+1;
    }
    init(ret);
    for(int i=1;i<=ret;i++){
        for(int j=i;j<=ret;j++){
            if(ret%2==0&&i==j-1&&i%2==0) continue;
            adj[i].push_back({j,++etot});
            adj[j].push_back({i,etot});
        }
    }
    dfs(1);
    reverse(st.begin(),st.end());
    for(auto p:st){
        if(!n) break;
        n--;
        cout<<prime[p-1]<<' ';
        vis[p]=0;
    }
    cout<<'\n';
}

int main(){
    initpri(3e5);
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}