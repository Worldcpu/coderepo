#include<bits/stdc++.h>
using namespace std;
constexpr int N=10;

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

signed main(){
    srand(time(0));
    int m=getrd(1,5);
    cout<<N<<' '<<m<<'\n';
    for(int i=1;i<=N;i++){
        int len=getrd(2,5);
        for(int i=1;i<=len;i++){
            cout<<(char)('a'+getrd(0,2));
        }
        cout<<' '<<getrd(100,1000)<<'\n';
    }
    for(int i=1;i<=m;i++){
        int len=getrd(14,54);
        for(int i=1;i<=len;i++){
            cout<<(char)('a'+getrd(0,2));
        }
        cout<<' '<<getrd(1,2)<<'\n';
    }
    
    return 0;
}