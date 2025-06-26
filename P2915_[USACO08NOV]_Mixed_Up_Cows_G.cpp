#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1<<17,MK=17;
int f[MK][MN],n,K,a[MK];


int main(){
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[i][(1<<(i-1))]=1;
    }
    for(int s=0;s<(1<<n);s++){
        for(int i=1;i<=n;i++){
            if(!(s&(1<<(i-1)))) continue;
            for(int j=1;j<=n;j++){
                if(s&(1<<(j-1))) continue;
                if(abs(a[j]-a[i])>K){
                    f[j][(1<<(j-1))|s]+=f[i][s];
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=f[i][(1<<n)-1];
    }
    cout<<ans;
    return 0;
}
