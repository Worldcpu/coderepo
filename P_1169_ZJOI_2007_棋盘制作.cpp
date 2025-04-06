#include<iostream>
using namespace std;
int n,m;
const int MN=2048;
int map[MN][MN],l[MN][MN],r[MN][MN],up[MN][MN],ans1=-1,ans2=-1;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>map[i][j];
            up[i][j]=1;
            l[i][j]=j;
            r[i][j]=j;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            if(map[i][j]!=map[i][j-1]){
                l[i][j]=l[i][j-1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m-1;j>=1;j--){
            if(map[i][j]!=map[i][j+1]){
                r[i][j]=r[i][j+1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i>1&&map[i][j]!=map[i-1][j]){
                up[i][j]=up[i-1][j]+1;
                l[i][j]=max(l[i][j],l[i-1][j]);
                r[i][j]=min(r[i][j],r[i-1][j]);
            }
            int len=r[i][j]-l[i][j]+1,h=up[i][j];
            int p=min(len,h);
            ans1=max(ans1,p*p);
            ans2=max(ans2,len*h);
        }
    }
    cout<<ans1<<endl<<ans2;
    return 0;
}