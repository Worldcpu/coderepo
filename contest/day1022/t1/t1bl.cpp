#include<bits/stdc++.h>
using namespace std;
int n,a,b;

bool check(int x){
    int tmp=n-x;
    if(tmp%(a+b)>a||tmp%(a+b)==0){
        return 1;
    }
    return 0;
}

void solve(){
    cin>>n>>a>>b;
    for(int i=0;i<n;i++){
        if(check(i)){
            cout<<i<<'\n';
            return;
        }
    }
    cout<<"Sayonara\n";
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}