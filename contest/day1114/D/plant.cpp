#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520,MOD=1e9+7;
int n,m,c,s[MN][MN],cf[MN],tar[MN];


int main(){
    cin>>n>>m>>c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[i][j];
        }
    }
    if(n==1&&m==1){
        cout<<s[1][1]<<'\n';
    }
    return 0;
}