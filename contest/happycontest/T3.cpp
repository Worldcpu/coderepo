#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520,MM=1e5+15;
int f[MN][MM],n,m,K,a[MN],b[MN],suma,sumb;


int main(){
    freopen("contest.in","r",stdin);
    freopen("contest.out","w",stdout);
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]<K){
            cout<<"Impossible\n";
            return 0;
        }
        suma+=a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    memset(f,128,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=m;i++){
        sumb+=b[i];
        for(int j=0;j<=sumb;j++){
            f[i][j]=max(f[i][j],f[i-1][j]);
            if(j-b[i]>=0) f[i][j]=max(f[i][j],f[i-1][j-b[i]]+min(n,b[i])); 
        }
    }
    for(int j=suma;j<=sumb;j++){
        if(f[m][j]>=n*K){
            cout<<j-suma;
            return 0;
        }
    }
            cout<<"Impossible\n";
    return 0;
}