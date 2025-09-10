#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,m;
int fx[4]={0,0,1,-1},fy[4]={1,-1,0,0};
char mp[MN][MN];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='#'){
                int cnt=0;
                for(int k=0;k<4;k++){
                    int nx=i+fx[k],ny=j+fy[k];
                    if(nx>=1 && nx<=n && ny>=1 && ny<=m){
                        cnt+=mp[nx][ny]=='#';
                    }
                }
                if(cnt!=2 && cnt!=4){
                    cout<<"No";
                    return 0;
                }
            }
        }
    }
    cout<<"Yes";
    return 0;
}
