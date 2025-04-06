#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
const int MN=128;
int n,t;
int fx[5]={1,-1,0,0},fy[5]={0,0,1,-1};
pir p[MN][MN];
bool vis[MN][MN],stop[MN][MN];

bool match(pir a){
    int ax=a.first,ay=a.second;
    for(int i=0;i<4;i++){
        int nx=ax+fx[i],ny=ay+fy[i];
        if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&!vis[nx][ny]&&!stop[nx][ny]){
            vis[nx][ny]=1;
            if(!p[nx][ny].first||match(p[nx][ny])){
                p[nx][ny]=pir(ax,ay);
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    cin>>n>>t;
    for(int i=1;i<=t;i++){
        int x,y;
        cin>>x>>y;
        stop[x][y]=1;
    }
    int ret=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(((i+j)&1)&&!stop[i][j]){
                memset(vis,0,sizeof(vis));
                ret+=match(pir(i,j));
            }
        }
    }
    cout<<ret;
    return 0;
}