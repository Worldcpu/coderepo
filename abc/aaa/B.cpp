#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,a[MN];



int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    n=unique(a+1,a+1+n)-a-1;
    cout<<n<<'\n';
    for(int i=1;i<=n;i++){
        cout<<a[i]<<' ';
    }

    return 0;
}