#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
typedef pair<int,int> pir;
//v fa
struct node{
	int v,fa,dep;
};
int n;
int siz[MN],ans1[MN],ans2[MN];
vector<int> adj[MN];
void bfs(){
	queue<node> q;
	node start={1,0,1};
	q.push(start);
	while(!q.empty()){
		node f=q.front();
		q.pop();
		int u=f.v,fa=f.fa,d=f.dep;
		for(auto v:adj[u]){
			if(v!=fa){
				ans1[v]=d+1;
				q.push({v,u,d+1});
			}
		}
	}
}
void dfs(int u,int fa){
	siz[u]=1;
	for(auto v:adj[u]){
		if(v!=fa){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
}
void dfs2(int u,int fa){
	if(adj[u].size()==1){
		ans2[u]=siz[1];
	}else{
		int tmp=0;
		for(auto v:adj[u]){
			if(v!=fa){
				dfs2(v,u);
				tmp+=siz[v];
			}
		}
		ans2[u]=siz[1]-tmp;
	}
}
int main(){
	cin>>n;
	ans1[1]=ans2[1]=1;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	bfs();
	dfs(1,0);
	dfs2(1,0);
	ans2[1]=1;
	for(int i=1;i<=n;i++){
		cout<<ans1[i]<<" "<<ans2[i]<<'\n';
	}
	return 0;
}