#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5200;
int n,f[MN],g[MN][MN],ans;
string st;

void init(){
    for(int i=0;i<=n;i++){
        f[i]=0;
        for(int j=0;j<=n;j++) g[i][j]=0;
    }
}

bool isok(int x,int y){
    int lcpp=g[x][y];
    if(x+lcpp>n+1) return 0;
    if(st[x+lcpp]>st[y+lcpp]) return 1;
    return 0;
}

int getf(int x,int y){
    if(!isok(x,y)) return 0;
    return f[y]+n-x-g[x][y]+1;
}

void solve(){
    cin>>n>>st;
    init();
    st=" "+st;
    for(int i=n-1;i>=1;i--){
        g[n][i]=(st[i]==st[n]);
    }
    for(int i=n-1;i>=1;i--){
        for(int j=i-1;j>=1;j--){
            g[i][j]=(st[i]==st[j])?(g[i+1][j+1]+1):0;
        }
    }
    f[1]=ans=n;
    for(int i=2;i<=n;i++){
        f[i]=n-i+1;
        for(int j=1;j<i;j++){
            f[i]=max(f[i],getf(i,j));
        }
        ans=max(ans,f[i]);
    }
    cout<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}