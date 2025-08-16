#include<bits/stdc++.h>
using namespace std;
constexpr int MN=620;
int T,n,a[MN][MN];

namespace HLS{

    int solve(){
        int ret=1,w=1;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                while(a[i][i]){
                    int div=a[j][i]/a[i][i];
                    for(int k=i;k<=n;k++){
                        a[j][k]=(a[j][k]-1ll*div*a[i][k]);
                    }
                    swap(a[i],a[j]);
                    w=-w;
                }
                swap(a[i],a[j]);
                w=-w;
            }
        }
        for(int i=1;i<=n;i++){
            ret=1ll*a[i][i]*ret;
        }
        ret=1ll*w*ret;
        return (ret);
    }

}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        for(int j=1;j<=n;j++){
            if(j>=l&&j<=r) a[i][j]=1;
            else a[i][j]=0;
        }
    }
    int ret=HLS::solve();
    if(ret==0) cout<<"tie\n";
    else if(ret<0) cout<<"xx\n";
    else cout<<"pp\n";
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}