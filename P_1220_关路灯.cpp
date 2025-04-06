#include<iostream>
#include<cstring>
using namespace std;
const int MN=100;
int n,c;
int pw[MN],pos[MN],t[MN],f[MN][MN][2];
int getv(int u,int v,int l,int r){
    return abs(pos[u]-pos[v])*(pw[n]-(pw[r]-pw[l-1]));
}
int main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        cin>>pos[i]>>pw[i];
        pw[i]+=pw[i-1];
    }
    memset(f,0x3f,sizeof(f));
    f[c][c][0]=f[c][c][1]=0;
    for(int l=c;l>=1;l--){
        for(int r=c;r<=n;r++){
            if(l>1){
                f[l-1][r][0]=min(f[l-1][r][0],f[l][r][0]+getv(l,l-1,l,r));
                f[l-1][r][0]=min(f[l-1][r][0],f[l][r][1]+getv(r,l-1,l,r));
            }
            if(r<n){
                f[l][r+1][1]=min(f[l][r+1][1],f[l][r][1]+getv(r+1,r,l,r));
                f[l][r+1][1]=min(f[l][r+1][1],f[l][r][0]+getv(r+1,l,l,r));
            }
        }
    }
    cout<<min(f[1][n][0],f[1][n][1]);
    return 0;
}