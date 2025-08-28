#include<bits/stdc++.h>
using namespace std;
int f[4];


int main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        for(int j=1;j<=4;j++){
            f[j]=max(f[j-1],f[j]+((j&1)==(v&1)));
        }
    }
    cout<<f[4];
    return 0;
}