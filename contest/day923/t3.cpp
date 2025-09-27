#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
const int dx[]={0,1,0,-1,0},dy[]={1,0,-1,0,0};
int n,m,sum,sumd;
bool flag=1;
vector<char> mp[MN];
int a[1000005],ok[1000005];

int &ep (int a[],int x,int y) {
    return a[(x-1)*m+y];
}


int main(){
    freopen("indian.in","r",stdin);
    freopen("indian.out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        mp[i].reserve(m+1);
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='.') flag=0;
        }
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            if (mp[i][j]=='#') ep (a,i,j)=1,sumd++;
        }
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            if (ep (a,i,j)) {
                sum++;
                for (int d=0;d<4;d++) {
                    int nx=i+dx[d],ny=j+dy[d];
                    if (1>nx||nx>n||1>ny||ny>m||!ep(a,nx,ny)) sum++;
                }
            }
        }
    }
    sum/=5;
    if(flag){
        if(sum<m*n/2) return 0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if((j&1)) cout<<1;
                else cout<<0;
            }
            cout<<'\n';
        }
        return 0;
    }else{
        if(sumd>sum){
            return 0;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(mp[i][j]=='#') cout<<1;
                else cout<<'.';
            }
            cout<<'\n';
        }
    }
    return 0;
}