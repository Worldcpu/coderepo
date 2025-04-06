#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef pair<int,int> PIR;
const int MN=150;
PIR p[MN][MN];
int n,m;
bool used[MN][MN],vis[MN][MN];
int fx[5]={0,1,-1,0,0},fy[5]={0,0,0,1,-1};
bool match(int x,int y){
    for(int i=1;i<=4;i++){
        int dx=x+fx[i],dy=y+fy[i];
        if(dx>=1&&dx<=n&&dy>=1&&dy<=n&&!used[dx][dy]&&!vis[dx][dy]){
            vis[dx][dy]=1;
            PIR pr=p[dx][dy];
            if(pr.first==-1||match(pr.first,pr.second)){
                p[dx][dy]={x,y};
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        used[x][y]=1;
    }
    memset(p,-1,sizeof(p));
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!used[i][j]&&(i+j)&1){
                memset(vis,0,sizeof(vis));
                ans+=match(i,j);
            }
        }
    }
    cout<<ans;
    return 0;
}