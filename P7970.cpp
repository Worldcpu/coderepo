#include<bits/stdc++.h>
using namespace std;
constexpr int MN=65;
int f[MN][2],n,m,q;

int dfs(int x,int y){
    if(y<0||!x) return 0;
    x|=x-1;
    for(int i=1;i<=30;i++){
        f[i][0]=f[i][1]=0;
        int upx=(x>>i-1)&1,upy=(y>>i-1)&1;
        int tmp=f[i-1][0]+f[i-1][1];
        if(!upx){
            if(upy){
                f[i][0]+=f[i-1][0];
                f[i][1]+=f[i-1][1];
            }else f[i][1]+=tmp;
        }
        if(!upy){
            f[i][0]+=f[i-1][0];
            f[i][1]+=f[i-1][1];
        }else f[i][0]+=tmp;
    }
    return f[30][0];
}

int main(){
    cin>>n>>m>>q;
    f[0][0]=1;
    while(q--){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        if(!x1&&!y1){
            cout<<1<<'\n';
        }else{
            cout<<dfs(x1,y2)-dfs(x1,y1-1)+dfs(y1,x2)-dfs(y1,x1-1)<<'\n';
        }
    }

    return 0;
}