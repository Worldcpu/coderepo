#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520+15;
int T,n,K,cnt1,cnt2,cnt3;
int pos[MN][MN];
char mp[MN][MN],mp1[MN][MN],mp2[MN][MN],mp3[MN][MN];

void init(){
    cnt1=cnt2=cnt3=K=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            mp[i][j]=mp1[i][j]=mp2[i][j]=mp3[i][j]='\n';
        }
    }
}

void solve(){
    init();
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>mp[i][j];
            mp1[i][j]=mp2[i][j]=mp3[i][j]=mp[i][j];
            if(mp[i][j]!='.') K++;
            pos[i][j]=(i+j)%3;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(pos[i][j]==0&&mp[i][j]=='O') mp1[i][j]='X',cnt1++;
            if(pos[i][j]==1&&mp[i][j]=='X') mp1[i][j]='O',cnt1++;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(pos[i][j]==1&&mp[i][j]=='O') mp2[i][j]='X',cnt2++;
            if(pos[i][j]==2&&mp[i][j]=='X') mp2[i][j]='O',cnt2++;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(pos[i][j]==2&&mp[i][j]=='O') mp3[i][j]='X',cnt3++;
            if(pos[i][j]==0&&mp[i][j]=='X') mp3[i][j]='O',cnt3++;
        }
    }
    if(cnt1<=K/3){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) cout<<mp1[i][j];
            cout<<'\n';
        }
    }
    else if(cnt2<=K/3){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) cout<<mp2[i][j];
            cout<<'\n';
        }
    }
    else if(cnt3<=K/3){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) cout<<mp3[i][j];
            cout<<'\n';
        }
    }
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}
