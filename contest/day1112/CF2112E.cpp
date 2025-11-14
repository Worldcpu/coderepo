#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int f[MN],n;

void solve(){
    cin>>n;
    if(n%2==0){
        cout<<-1<<'\n';
    }
    else cout<<f[n]<<'\n';
}

void initf(){
    memset(f,0x3f,sizeof(f));
    f[1]=1;
    for(int i=2;i<MN;i++){
        for(int j=1;j*j<=i;j++){
            if(i%j==0){
                f[i]=min(f[i],f[j]+f[max(i/j-2,0)]);
                f[i]=min(f[i],f[i/j]+f[max(j-2,0)]);
            }
        }
    }
}

int main(){
    initf();
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}