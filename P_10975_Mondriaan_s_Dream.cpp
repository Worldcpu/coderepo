#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=12;
int n,m,vis[1<<MN];
ll f[MN][1<<MN];
int main(){
    while (cin>>n>>m)
    {
        if(n==0&&m==0) break;
        memset(f,0,sizeof(f));
        f[0][0]=1;
        for(int i=0;i<(1<<m);i++){
            bool cnt=0,ji=0;
            for(int j=0;j<m;j++){
                if((i>>j)&1){
                    ji|=cnt;
                    cnt=0;
                }else cnt^=1;
            }
            vis[i]=ji|cnt ? 0 : 1;
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<(1<<m);j++){
                for(int k=0;k<(1<<m);k++){
                    if((j&k)==0&&vis[j|k]){
                        f[i][j]+=f[i-1][k];
                    }
                }
            }
        }
        cout<<f[n][0]<<'\n';
    }
    
    return 0;
}