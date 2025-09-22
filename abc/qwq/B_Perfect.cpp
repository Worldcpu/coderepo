#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,K,st[MN],ans;
bool vis[MN];

int main(){
    cin>>n>>m>>K;
    for(int i=1;i<=K;i++){
        int a,b;
        cin>>a>>b;
        st[a]|=(1<<b-1);
        if(st[a]==(1<<m)-1&&!vis[a]){
            vis[a]=1;
            cout<<a<<' ';
        }
    }

    return 0;
}