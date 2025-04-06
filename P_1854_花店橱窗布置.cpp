#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=256;

struct previous{
    int i,j;
}pre[MN][MN];
vector<int> ans;
int n,m;
int f[MN][MN];
int a[MN][MN];

void getans(int i,int j){
    while (1)
    {
        if(i==0) break;
        previous p=pre[i][j];
        if(i!=p.i){
            ans.push_back(j);
        }
        i=p.i;
        j=p.j;
    }
    for(int i=ans.size()-1;i>=0;i--){
        cout<<ans[i]<<" ";
    }
}

int main(){
    memset(f,128,sizeof(f));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int j=0;j<=m;j++){
        f[0][j]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=m;j++){
            // f[i][j]=max(f[i][j-1],f[i-1][j-1]+a[i][j]);
            if(f[i][j-1]<f[i-1][j-1]+a[i][j]){
                f[i][j]=f[i-1][j-1]+a[i][j];
                pre[i][j]={i-1,j-1};
            }else{
                f[i][j]=f[i][j-1];
                pre[i][j]={i,j-1};
            }
        }
    }
    cout<<f[n][m]<<'\n';
    getans(n,m);

    return 0;
}