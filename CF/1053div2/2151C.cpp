#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int a[MN],b[MN],n,m;

void init(){

}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        b[i]=a[i+1]-a[i];
        m+=i*b[i];
    }
    for(int k=1;k<=n;k++){
        priority_queue<int> pq;
    }

}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}