#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,p,v;
unordered_map<int,int> f;


signed main(){
    cin>>n>>p>>v;
    f[0]=1;
    for(int i=1;;i++){
        for(int j=2;j<=(i-v)/p;j++){
            f[i]=max(f[i],f[i-v-j*p]*j);
        }
        if(f[i]>=n){
            cout<<i;
            break;
        }
    }
    return 0;
}