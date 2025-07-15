#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int n,m,cnt1,cnt2;
char mp[MN][MN],fmp[MN][MN];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            fmp[i][j]=mp[i][j]=='X'?'.':'X';
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char awa;
            cin>>awa;
            if(awa!=mp[i][j]) cnt1++;
            if(awa!=fmp[i][j]) cnt2++;
        }
    }
    if(cnt1<=cnt2){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cout<<mp[i][j];
            cout<<'\n';
        }
    }else{
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cout<<fmp[i][j];
            cout<<'\n';
        }
    }

    return 0;
}
