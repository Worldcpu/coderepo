#include<iostream>
using namespace std;
const int MN=1200;
int n,m,l[MN][MN],r[MN][MN],up[MN][MN],ans=-1;
char map[MN][MN];
int main(){
    cin>>n>>m;
    bool islegal=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>map[i][j];
            if(map[i][j]=='F'){
                islegal=1;
            }
            up[i][j]=1;
            l[i][j]=r[i][j]=j;
        }
    }
    if(!islegal){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            if(map[i][j]=='F'&&map[i][j]==map[i][j-1]){
                l[i][j]=l[i][j-1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m-1;j>=1;j--){
            if(map[i][j]=='F'&&map[i][j]==map[i][j+1]){
                r[i][j]=r[i][j+1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i>1&&map[i][j]=='F'&&map[i][j]==map[i-1][j]){
                up[i][j]=up[i-1][j]+1;
                l[i][j]=max(l[i][j],l[i-1][j]);
                r[i][j]=min(r[i][j],r[i-1][j]);
            }
            int len=r[i][j]-l[i][j]+1,h=up[i][j];
            ans=max(ans,len*h);
        }
    }
    cout<<3*ans;
    return 0;
}