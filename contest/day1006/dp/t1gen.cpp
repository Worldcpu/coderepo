#include<bits/stdc++.h>
using namespace std;

int getrd(int l,int r){
    return rand()%(r-l+1)+l;
}

int main(){
    srand(time(0));    
    int n=2e5;
    cout<<n<<'\n';
    for(int i=1;i<=n;i++){
        cout<<getrd(0,n)<<' ';
    }
    return 0;
}