#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int INF = (int)4e18;

struct DSU {
    int n;
    vector<int> p;
    DSU(int n=0){init(n);}
    void init(int n_){ n=n_; p.resize(n+2); for(int i=0;i<=n+1;i++) p[i]=i; }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    void unite_to(int x,int y){ p[find(x)] = find(y); }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if(!(cin>>N)) return 0;
    vector<int> S(N+1), T(N+1);
    for(int i=1;i<=N;i++) cin>>S[i];
    for(int i=1;i<=N;i++) cin>>T[i];
    // collect start points and sort
    vector<pair<int,int>> sv; sv.reserve(N);
    for(int i=1;i<=N;i++) sv.emplace_back(S[i], i);
    sort(sv.begin(), sv.end()); // by S coordinate
    // position of each person in sorted starts (0-based)
    vector<int> spos(N+1);
    for(int i=0;i<N;i++) spos[sv[i].second]=i;
    // build adjacency using DSU-skip to avoid revisiting same start index many times
    vector<vector<int>> adj(N+1);
    vector<int> indeg(N+1,0);
    DSU dsu(N); // indices 0..N-1 for starts
    for(int i=1;i<=N;i++){
        int p1 = spos[i];
        if(S[i] < T[i]){
            int l = p1 + 1;
            int ub = upper_bound(sv.begin(), sv.end(), pair<int,int>(T[i], (int)1e9)) - sv.begin();
            int r = ub - 1;
            if(l<=r){
                int k = dsu.find(l);
                while(k<=r){
                    int j = sv[k].second;
                    adj[j].push_back(i);
                    cerr<<j<<' '<<i<<'\n';
                    indeg[i]++;
                    dsu.unite_to(k, k+1);
                    k = dsu.find(k);
                }
            }
        }else if(S[i] > T[i]){
            int lb = lower_bound(sv.begin(), sv.end(), pair<int,int>(T[i], -1)) - sv.begin();
            int l = lb;
            int r = p1 - 1;
            if(l<=r){
                int k = dsu.find(l);
                while(k<=r){
                    int j = sv[k].second;
                    adj[j].push_back(i);
                    cerr<<j<<' '<<i<<'\n';
                    indeg[i]++;
                    dsu.unite_to(k, k+1);
                    k = dsu.find(k);
                }
            }
        }
    }

    deque<int> q;
    for(int i=1;i<=N;i++) if(indeg[i]==0) q.push_back(i);
    vector<int> order; order.reserve(N);
    while(!q.empty()){
        int u=q.front(); q.pop_front();
        order.push_back(u);
        for(int v: adj[u]){
            indeg[v]--;
            if(indeg[v]==0) q.push_back(v);
        }
    }
    if((int)order.size()!=N){
        cout<<"No\n";
    }else{
        cout<<"Yes\n";
        for(int i=0;i<N;i++){
            if(i) cout<<' ';
            cout<<order[i];
        }
        cout<<"\n";
    }
    return 0;
}
