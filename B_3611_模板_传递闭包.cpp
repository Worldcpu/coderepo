#include<bits/stdc++.h>
using namespace std;
constexpr int MN=150;
bool mp[MN][MN];
int n;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>mp[i][j];
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                mp[i][j]|=(mp[i][k]&mp[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<mp[i][j]<<" ";
        }
        cout<<'\n';
    }
    return 0;
}