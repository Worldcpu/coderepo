#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int T,n,m,q;
vector<int> adj[MN];

namespace Tree{
    int odd[MN],even[MN],bel[MN],dtot;

void dfs(int u, int father, int id){
    bel[u]=id;
	for(auto v:adj[u]){
		if(v==father) continue;
		if(odd[u]&&!even[v]){
			even[v]=true;
			dfs(v,u,id);
		}
		if(even[u]&&!odd[v]){
			odd[v]=true;
			dfs(v,u,id);
		}
	}
}

}using namespace Tree;

int main(){
    cin>>T>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=0;i<=n;i++){
        if(!bel[i]){
            dtot++;
            even[i]=1;
            dfs(i,i,dtot);
        }
    }
    cin>>q;
    while(q--){
        int s,t;
        cin>>s>>t;
        if(bel[s]!=bel[t]){
            cout<<-1<<'\n';
            continue;
        }
        if(s==t){
            cout<<0<<'\n';
            continue;
        }
        if((even[s]&&odd[t])||(even[t]&&odd[s])) cout<<1<<'\n';
        else cout<<2<<'\n';
    }
    return 0;
}