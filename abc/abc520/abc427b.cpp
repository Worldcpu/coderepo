#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1220;
int n,a[MN];

int f(int x){
    int ret=0;
    while(x){
        ret+=x%10;
        x/=10;
    }
    return ret;
}

int main(){
    cin>>n;
    a[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i-1;j++){
            a[i]+=f(a[j]);
        }
    }
    cout<<a[n];

    return 0;
}