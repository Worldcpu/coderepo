#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int MN=1e6+15;
const ull P=114514191981019;
random_device rd;
mt19937 mt;

set<ull> s;
int n;
ull f[MN],xorp;
vector<int> adj[MN];

ull xorshift(ull x){
    x^=xorp;
    x^=(x<<3);
    x^=(x>>5);
    x^=(x<<7);
    x^=(x>>9);
    return x+P;
}

void dfs(int u,int fa){
    f[u]=0;
    for(auto v:adj[u]){
        if(v==fa) continue;
        dfs(v,u);
        f[u]+=xorshift(f[v]);
    }
    f[u]+=xorp;
    s.insert(f[u]);
}

int main(){
    mt.seed(rd());
    xorp=mt();
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    cout<<s.size();
    return 0;
}