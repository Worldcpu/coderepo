#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,f[MN][3],x[MN];

void init(){
    for(int i=1;i<=n;i++){
        f[i][0]=f[i][1]=f[i][2]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>x[i];
    }
    f[1][0]=f[1][1]=f[1][2]=1;
    for(int i=2;i<=n;i++){
        if(f[i-1][0]){
            f[i][0]=f[i-1][0]*(x[i]-x[i-1]==1);
            f[i][1]=f[i-1][0]*(x[i]-1-x[i-1]==1);
            f[i][2]=f[i-1][0]*(x[i]+1-x[i-1]==1);
        }
        if(f[i-1][1]){
            f[i][0]=f[i-1][1]*(x[i]-(x[i-1]-1)==1);
            f[i][1]=f[i-1][1]*(x[i]-1-(x[i-1]-1)==1);
            f[i][2]=f[i-1][1]*(x[i]+1-(x[i-1]-1)==1);
        }
        if(f[i-1][2]){
            f[i][0]=f[i-1][2]*(x[i]-(x[i-1]+1)==1);
            f[i][1]=f[i-1][2]*(x[i]-1-(x[i-1]+1)==1);
            f[i][2]=f[i-1][2]*(x[i]+1-(x[i-1]+1)==1);
        }
    }
    cout<<((f[n][0]||f[n][1]||f[n][2])?"YES":"NO")<<'\n';

}


int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}