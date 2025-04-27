#include<bits/stdc++.h>
using namespace std;
int main(){
    int ans=0;
    for(int i=1;i<=15;i++){
        if(i&1){
            cout<<i<<" "<<(i^(i+1))<<'\n';
        }
    }
    cout<<ans;
    return 0;
}