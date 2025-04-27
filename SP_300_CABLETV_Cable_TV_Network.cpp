#include<bits/stdc++.h>
#define ls(p) (p<<1)
#define rs(p) (p<<1|1)
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5;
constexpr int INF=1e9;
struct Edge{
    int v,w,id;
};
struct SEdge{
    int u,v,idz,idf;
}e[MN];
int n,m,S,T,etot,dep[MN],cur[MN],ans;
vector<Edge> adj[MN];

void add(int u,int v,int w){
    int us=adj[u].size(),vs=adj[v].size();
    adj[u].push_back({v,w,vs});
    adj[v].push_back({u,0,us});
    e[++etot]={u,v,us,vs};
}

bool bfs(){
    memset(dep,-1,sizeof(dep));
    queue<int> q;
    q.push(S);
    dep[S]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto e:adj[u]){
            if(dep[e.v]==-1&&(e.w)){
                dep[e.v]=dep[u]+1;
                q.push(e.v);
            }
        }
    }
    memset(cur,0,sizeof(cur));
    return (dep[T]!=-1);
}

int dfs(int u,int lim){
    if(u==T) return lim;
    int flow=0;
    for(int i=cur[u];i<adj[u].size();i++){
        cur[u]=i;
        auto e=adj[u][i];
        if(dep[e.v]==dep[u]+1&&(e.w)){
            int p=dfs(e.v,min(lim,e.w));
            if(p){
                adj[u][i].w-=p;
                adj[e.v][e.id].w+=p;
                return p;
            }else dep[e.v]=-1;
        }
    }
    return 0;
}

int dinic(){
    int ans=0,flow=0;
    while(bfs()){
        while(flow=dfs(S,INF)){
            ans+=flow;
        }
    }
    return ans;
}

pir div(string s)
{
	int x = 0, y = 0;
	bool flag = false;
	s.erase(0, 1);
	s.erase(s.size() - 1, 1);
	for (int i = 0; i < s.size(); i++)
		if (s[i] == ',')
			flag = true;
		else
		{
			if (!flag)
				x = x * 10 + s[i] - '0';
			else
				y = y * 10 + s[i] - '0';
		}
	return make_pair(x, y);
}

void init(){
    for(int i=0;i<=(n<<1);i++) adj[i].clear();
    ans=n;
    etot=0;
}

void solve(){

    cin>>n>>m;
    init();
    for(int i=0;i<n;i++){
        add(ls(i),rs(i),1);
    }
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        pir sp=div(s);
        add(rs(sp.first),ls(sp.second),INF);
        add(rs(sp.second),ls(sp.first),INF);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            S=rs(i);
            T=ls(j);
            ans=min(ans,dinic());
            // cout<<"AWA"<<'\n';
            for(int i=1;i<=etot;i++){
                adj[e[i].u][e[i].idz].w+=adj[e[i].v][e[i].idf].w;
                adj[e[i].v][e[i].idf].w=0;
            }
        }
    }
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}