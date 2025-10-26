#include<bits/stdc++.h>
using namespace std;
constexpr int N=100;

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

signed main(){
    srand(time(0));
    int m=getrd(100,1000);
    cout<<N<<' '<<m<<'\n';
    for(int i=1;i<=N;i++){
        int len=getrd(3,8);
        for(int i=1;i<=len;i++){
            cout<<(char)('a'+getrd(0,3));
        }
        cout<<' '<<getrd(3,5)<<'\n';
    }
    for(int i=1;i<=m;i++){
        int len=getrd(10,15);
        for(int i=1;i<=len;i++){
            cout<<(char)('a'+getrd(0,3));
        }
        cout<<' '<<getrd(1,10)<<'\n';
    }
    
    return 0;
}