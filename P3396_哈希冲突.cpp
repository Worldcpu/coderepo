#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MB=400,MN=2e5+15;
int n,m,a[MN],ans[MB][MB];


signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=sqrt(n);j++){
            ans[j][i%j]+=a[i];
        }
    }
    while(m--){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='A'){
            if(x<=sqrt(n)){
                cout<<ans[x][y]<<'\n';
            }else{
                int ret=0;
                for(int i=y;i<=n;i+=x) ret+=a[i];
                cout<<ret<<'\n';
            }
        }else{
            for(int i=1;i<=sqrt(n);i++) ans[i][x%i]+=y-a[x];
            a[x]=y;
        }
    }
    return 0;
}
