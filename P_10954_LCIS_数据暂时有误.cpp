#include<bits/stdc++.h>
using namespace std;
const int MN=5000;
int n,a[MN],b[MN],f[MN][MN];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=n;i++){
        int val=0;
        for(int j=1;j<=n;j++){
            if(a[i]==b[j]){
                f[i][j]=val+1;
            }else f[i][j]=f[i-1][j];
            if(a[i]>b[j]) val=max(val,f[i-1][j]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,f[n][i]);
    }
    cout<<ans;
    return 0;
}