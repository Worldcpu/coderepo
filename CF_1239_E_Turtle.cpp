#include<bits/stdc++.h>
using namespace std;
constexpr int MN=55,MV=1300000;
int n,m,suma,a[MN],b[MV];
bitset<MV> f[MN][MN];

void dfs(int n,int m,int i){
    if(!m) return;
    if(f[n-1][m][i]){
        dfs(n-1,m,i);
        return;
    }
    if(i>=a[n]&&f[n-1][m-1][i-a[n]]){
        b[a[n]]--;
        dfs(n-1,m-1,i-a[n]);
        cout<<a[n]<<' ';
    }
}

int main(){
    cin>>n;
    m=n<<1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=n+1;i<=n<<1;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+m);
    for(int i=3;i<=m;i++){
        b[a[i]]++;
        suma+=a[i];
    }
    f[2][0]=1;
    for(int i=3;i<=m;i++){
        for(int j=0;j<n;j++){
            f[i][j]|=f[i-1][j];
            if(j) f[i][j]|=f[i-1][j-1]<<a[i];
        }
    }
    suma/=2;
    for(int i=suma;i>=0;i--){
        if(f[m][n-1][i]){
            cout<<a[1]<<' ';
            dfs(m,n-1,i);
            cout<<'\n';
            for(int j=5e4;j>=0;j--){
                while(b[j]--) cout<<j<<" ";
            }
            cout<<a[2]<<'\n';
            return 0;
        }
    }
    return 0;
}