#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int K;


signed main(){
    cin>>K;
    cout<<50<<'\n';
    for(int i=0;i<50;i++){
        cout<<i+(K+i)/50<<' ';
    }

    return 0;
}