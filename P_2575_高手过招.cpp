#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520,MM=22;
int n,ans;
bool p[MN][MM];

void init(){
    for(int i=0;i<=n;i++){
        memset(p[i],0,sizeof(p[i]));
    }
    ans=0;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        int m;
        cin>>m;
        for(int j=1;j<=m;j++){
            int x;
            cin>>x;
            p[i][x]=1;
        }
    }
    for(int i=1;i<=n;i++){
        int cnt=0,tot=0;
        for(int j=20;j>=0;j--){
            if(!p[i][j]){
                if(tot){
                    ans^=tot;
                    tot=0;
                }
                cnt^=1;
            }else if(cnt) ++tot;
        }
        if(tot) ans^=tot;
    }
    cout<<(ans?"YES":"NO")<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}