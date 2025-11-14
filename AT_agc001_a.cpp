#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int n,a[MN],ans;


int main(){
    cin>>n;
    n<<=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i+=2){
        ans+=a[i];
    }
    cout<<ans;

    return 0;
}