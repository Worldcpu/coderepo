#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=302,INF=0x3f3f3f3f3f3f3f3f;
struct Node{
    int x,v;
}a[MN];
int n,f[MN][MN][MN][2],ans=-INF;

bool cmp(Node x,Node y){
    return x.x<y.x;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].v;
    }
    a[++n]={0,0};
    sort(a+1,a+1+n,cmp);
    memset(f,128,sizeof(f));
    for(int i=1;i<=n;i++){
        if(a[i].x==0&&a[i].v==0){
            for(int j=0;j<=n;j++){
                f[i][i][j][0]=0;
            }
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=i;j<=n;j++){
            for(int k=1;k<=n;k++){
                f[i][j][k][0]=max(f[i][j][k][0],f[i][j][k][1]-(a[j].x-a[i].x)*k);
                f[i][j][k][1]=max(f[i][j][k][1],f[i][j][k][0]-(a[j].x-a[i].x)*k);
                int cj=(a[j+1].x-a[j].x)*k,ci=(a[i].x-a[i-1].x)*k;
                if(j<n){
                    f[i][j+1][k][1]=max(f[i][j+1][k][1],f[i][j][k][1]-cj);
                    f[i][j+1][k-1][1]=max(f[i][j+1][k-1][1],f[i][j][k][1]-cj+a[j+1].v);
                }
                if(i>1){
                    f[i-1][j][k][0]=max(f[i-1][j][k][0],f[i][j][k][0]-ci);
                    f[i-1][j][k-1][0]=max(f[i-1][j][k-1][0],f[i][j][k][0]-ci+a[i-1].v);
                }
            }
        }
    }

    cout<<max(f[1][n][0][0],f[1][n][0][1]);
    return 0;
}