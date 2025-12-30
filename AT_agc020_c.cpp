#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5200,MV=5e6+15;
int n,a[MN],sum;
bitset<MV> f[2];


int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) sum+=a[i];
    int now=0,lst=1;
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        now^=1,lst^=1;
        f[now].reset();
        f[now]=f[lst]|(f[lst]<<a[i]);
    }
    for(int i=((sum+1)>>1);i<=sum;i++){
        if(f[now][i]){
            cout<<i<<'\n';
            break;
        }
    }

    return 0;
}