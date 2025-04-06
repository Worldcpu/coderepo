#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int map[160][160]{},vis[160][160]{},c,r;
struct node{
	int ni,nj,step;
};
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int bfs(node start){
	queue<node> q;
	q.push(start);
	int ans;
	vis[start.ni][start.nj]=1;
	while(!q.empty()){
		node f=q.front();
		q.pop();
		if(map[f.ni][f.nj]==2){
			ans=f.step;
			break;
		}
		for(int i=0;i<8;i++){
			int di=f.ni+dx[i],dj=f.nj+dy[i];
			if(di>=1&&di<=c&&dj>=1&&dj<=r&&vis[di][dj]==0&&map[di][dj]!=1){
				vis[di][dj]=1;
				node nd;
				nd.ni=di;
				nd.nj=dj;
				nd.step=f.step+1;
				q.push(nd);
			}
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ans.in","r",stdin);
#endif
	cin>>r>>c;
	int si,sj;
	for(int i=1;i<=c;i++){
		for(int j=1;j<=r;j++){
			char awa;
			cin>>awa;
			if(awa=='*') map[i][j]=1;
			else if(awa=='K'){
				si=i;
				sj=j;
				map[i][j]=0;
			}
			else if(awa=='H'){
				map[i][j]=2;
			}else map[i][j]=0;
		}
	}
	node st={si,sj,0};
	cout<<bfs(st);
	return 0;
}
