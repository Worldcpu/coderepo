#include<bits/stdc++.h>
using namespace std;
const int MN=1e4+15;
int m,n,f[MN],a[MN];
int main(){
    cin>>n>>m;
    f[0]=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=a[i];j--){
            f[j]+=f[j-a[i]];
        }
    }
    cout<<f[m];
    return 0;
}