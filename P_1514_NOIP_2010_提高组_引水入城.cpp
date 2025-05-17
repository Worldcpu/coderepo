#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int fx[5]={1,-1,0,0},fy[5]={0,0,1,-1};
int n,m,h[MN][MN],r[MN];
bool vis[MN][MN];

void clearvis(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            vis[i][j]=0;
        }
    }
}

void dfs(int x,int y){
    vis[x][y]=1;
    for(int i=0;i<4;i++){
        int nx=x+fx[i],ny=y+fy[i];
        if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&h[nx][ny]<h[x][y]&&!vis[nx][ny]){
            dfs(nx,ny);
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>h[i][j];
        }
    }
    for(int i=1;i<=m;i++){
        clearvis();
        dfs(1,i);
        int rk=1;
        for(int j=m;j>=1;j--){
            if(vis[n][j]){
                rk=j;
                break;
            }
        }
        for(int i=1;i<=m;i++){
            if(vis[n][i]) r[i]=max(r[i],rk);
        }
    }
    int cnt=0;
    for(int i=1;i<=m;i++) if(!r[i]) cnt++;
    if(cnt){
        cout<<0<<'\n'<<cnt;
        return 0;
    }
    cnt=1;
    int p=1;
    while(r[p]<m){
        p=r[p]+1;
        cnt++;
    }
    cout<<1<<'\n'<<cnt;
    return 0;
}
