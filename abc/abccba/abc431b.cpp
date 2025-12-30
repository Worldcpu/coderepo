#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,x,w[MN],q,wnow;
bool vis[MN];

int main(){
    cin>>wnow>>n;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    cin>>q;
    while(q--){
        int p;
        cin>>p;
        if(!vis[p]){
            wnow+=w[p];
            vis[p]=1;
        }else{
            wnow-=w[p];
            vis[p]=0;
        }
        cout<<wnow<<'\n';
    }


    return 0;
}