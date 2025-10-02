#include<bits/stdc++.h>
using namespace std;
constexpr int N=10,M=10;
constexpr char ch[11]={'9','9','9','9','9','9','9','9','9','+','*'};
int T;

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

int main(){
    srand(time(0));
    T=500;
    cout<<rand()<<' '<<T<<'\n';
    while(T--){
        cout<<N<<' '<<M<<'\n';
        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++){
                if((i==1&&j==1)||(i==N&&j==M)) cout<<ch[getrd(0,8)];
                else cout<<ch[getrd(0,10)];
            }
            cout<<'\n';
        }
    }
    
    return 0;
}