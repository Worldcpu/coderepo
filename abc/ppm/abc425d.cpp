#include <bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
struct Node{
    int x,y,stp;
};
int n,m,ans;
int fx[4]={0,0,1,-1},fy[4]={1,-1,0,0};
vector<vector<int>> bl;
vector<vector<char>> mp;
map<pir,int> vis;
queue<Node> q;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    mp.assign(n+1, vector<char>(m+1, '.'));
    bl.assign(n+1, vector<int>(m+1, 0));
    string row;
    for(int i=1;i<=n;i++){
        cin>>row;
        for(int j=1;j<=m;j++) mp[i][j]=row[j-1];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='#') continue;
            int cnt=0;
            for(int k=0;k<4;k++){
                int nx=i+fx[k], ny=j+fy[k];
                if(nx>=1&&nx<=n&&ny>=1&&ny<=m && mp[nx][ny]=='#') cnt++;
            }
            bl[i][j]=cnt;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='.' && bl[i][j]==1){
                q.push({i,j,1});
                mp[i][j]='#';
                vis[pir(i,j)]=1;
            }
        }
    }
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int qx=u.x+fx[i],qy=u.y+fy[i];
            if(qx>=1&&qx<=n&&qy>=1&&qy<=m&&mp[qx][qy]=='.'){
                bl[qx][qy]=0;
                for(int j=0;j<4;j++){
                    int nx=qx+fx[j],ny=qy+fy[j];
                    if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&mp[nx][ny]=='#'&&vis[pir(nx,ny)]<=u.stp){
                        bl[qx][qy]++;
                    }
                }
                if(bl[qx][qy]==1){
                    mp[qx][qy]='#';
                    q.push({qx,qy,u.stp+1});
                    vis[pir(qx,qy)]=u.stp+1;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans+=mp[i][j]=='#';
            cerr<<mp[i][j];
        }
        cerr<<'\n';
    }
    cout<<ans;

    return 0;
}
