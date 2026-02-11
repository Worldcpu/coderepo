#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n;
ll even,odd;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        ll x;
        cin>>x;
        if((x&1)){
            even++;
        }else odd++;
    }
    cout<<(even*(even-1)/2+odd*(odd-1)/2);
    return 0;
}