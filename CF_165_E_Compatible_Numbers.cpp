#include<bits/stdc++.h>
using namespace std;
constexpr int MN=23,MK=2e6+15;
int n,a[MK],f[1<<MN];


int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[a[i]]=a[i];
    }
    for(int i=0;i<22;i++){
        for(int j=0;j<(1<<22);j++){
            if((j>>i&1)&&f[j^(1<<i)]){
                f[j]=f[j^1<<i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        int x=((1<<22)-1)^a[i];
        cout<<(f[x]?f[x]:-1)<<" ";
    }
    

    return 0;
}