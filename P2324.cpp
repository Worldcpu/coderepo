#include<iostream>
using namespace std;
char goal[6][6]={
	{'0','0','0','0','0','0'},
	{'0','1','1','1','1','1'},
	{'0','0','1','1','1','1'},
	{'0','0','0','*','1','1'},
	{'0','0','0','0','0','1'},
	{'0','0','0','0','0','0'}
};
int fx[8]={1,1,-1,-1,2,2,-2,-2};
int fy[8]={2,-2,2,-2,1,-1,1,-1};
int T;
bool isok;
char map[6][6];
int geth(){
    int cnt=0;
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            if(map[i][j]!=goal[i][j]){
                cnt++;
            }
        }
    }
    return cnt;
}
void dfs(int x,int y,int dep,int mdep){
    if(dep==mdep){
        if(!geth()) isok=1;//答案找到了
        return;
    }
    for(int i=0;i<8;i++){
        int nx=x+fx[i],ny=y+fy[i];
        if(nx>=1&&nx<=5&&ny>=1&&ny<=5){
            swap(map[x][y],map[nx][ny]);
            if(dep+geth()<=mdep) dfs(nx,ny,dep+1,mdep);//如果预估深度足够，那么dfs
            if(isok) return;//如果有答案就返回
            swap(map[x][y],map[nx][ny]);
        }
    }
}

void solve(){
    int kx,ky;
    isok=0;
    for(int i=1;i<=5;i++){
        for(int j=1;j<=5;j++){
            cin>>map[i][j];
            if(map[i][j]=='*'){
                kx=i;
                ky=j;
            }
        }
    }
    for(int i=1;i<=15;i++){
        dfs(kx,ky,0,i);
        if(isok){
            cout<<i<<'\n';
            return;
        }
    }
    cout<<-1<<'\n';
}
int main(){
    // freopen("ans.in","r",stdin);
    cin>>T;
    while (T--)
    {
        solve();
    }
    
    return 0;
}