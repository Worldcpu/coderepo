#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15,MV=5e6;
int f[MN],n;


signed main(){
    cin>>n;
    for(int i=1;i<=MV;i++){
        for(int j=2*i;j<=n;j+=i){
            int c=j-i;
            if((j^i)==c) f[i]++;
        }
    }
    for(int i=1;i<=MV;i++) f[i]+=f[i-1];
    cout<<f[MV];

    return 0;
}