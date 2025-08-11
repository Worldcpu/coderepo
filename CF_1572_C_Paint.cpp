#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3520;
int f[MN][MN],n,a[MN];
vector<int> pos[MN];

void init(){
    for(int i=1;i<=n;i++){
        pos[i].clear();
        for(int j=1;j<=n;j++) f[i][j]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]].push_back(i);
    }
    for(int l=n;l>=1;l--){
        for(int r=l;r<=n;r++){
            f[l][r]=f[l+1][r];
            for(auto p:pos[a[l]]){
                if(l<p&&p<=r) f[l][r]=max(f[l][r],f[l+1][p-1]+1+f[p][r]);
            }
        }
    }
    cout<<n-f[1][n]-1<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}