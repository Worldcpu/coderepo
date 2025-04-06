#include<iostream>
using namespace std;
const int MN=520;
int n,m;
bool map[MN][MN];
int l[MN][MN],r[MN][MN],up[MN][MN];
int main(){
    cin>>n>>m;
    bool flag=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>map[i][j];
            if(map[i][j]) flag=1;
            up[i][j]=1;
            l[i][j]=r[i][j]=j;
        }
    }
    if(!flag){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            if(map[i][j]&&map[i][j]==map[i][j-1]){
                l[i][j]=l[i][j-1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m-1;j>=1;j--){
            if(map[i][j]&&map[i][j]==map[i][j+1]){
                r[i][j]=r[i][j+1];
            }
        }
    }
    int ans=-1e9;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i>1&&map[i][j]&&map[i][j]==map[i-1][j]){
                up[i][j]=up[i-1][j]+1;
                l[i][j]=max(l[i][j],l[i-1][j]);
                r[i][j]=min(r[i][j],r[i-1][j]);
            }
            int len=r[i][j]-l[i][j]+1,h=up[i][j];
            int p=min(len,h);
            ans=max(p,ans);
        }
    }
    cout<<ans;
    return 0;
}