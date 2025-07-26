#include<bits/stdc++.h>
using namespace std;
mt19937 mt;

auto getrand(int l,int r){
    return mt()%(r-l+1)+l;
}

int main(){
    mt.seed(time(0));
    int n=getrand(1,10),m=getrand(1,50);
    cout<<n<<" "<<m<<'\n';
    for(int i=1;i<=n;i++){
        cout<<getrand(1,10)<<" ";
    }
    cout<<'\n';
    for(int i=1;i<=n;i++){
        cout<<getrand(1,10)<<" ";
    }

    return 0;
}