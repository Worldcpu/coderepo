#include<bits/stdc++.h>
using namespace std;
int T;

int dfs(int x,int y,int p){
    if(x==y) return p;
    if(y/x>=2) return p;
    return dfs(y-x,x,p^1);
}

void solve(){
    int m,n;
    cin>>m>>n;
    if(m>n) swap(m,n);
    if(dfs(m,n,0)==0) cout<<"Stan wins\n";
    else cout<<"Ollie wins\n";
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
