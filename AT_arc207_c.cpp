#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int f[MN],g[MN],p[MN],a[MN],n;


int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,lst=1;i<=n;i++){
        for(int j=i;j>=1;j--){
            if((p[j]|a[i])==p[j]) break;
            p[j]|=a[i];
            if(g[j-1]<=p[j]) lst=max(lst,j);
        }
        f[i]=f[lst-1]+1;
        g[i]=p[lst];
    }
    cout<<f[n];

    return 0;
}