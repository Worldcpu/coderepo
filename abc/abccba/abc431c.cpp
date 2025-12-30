#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,K,it,h[MN],b[MN];

int main(){
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=1;i<=m;i++){
        cin>>b[i];
    }
    sort(h+1,h+1+n);
    sort(b+1,b+1+m);
    if(m<K){
        cout<<"No\n";
        return 0;
    }
    it=m-K+1;
    for(int i=1;i<=K;i++,it++){
        if(h[i]>b[it]){
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";
    

    return 0;
}