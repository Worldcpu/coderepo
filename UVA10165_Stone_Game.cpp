#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    while(1){
        cin>>n;
        if(!n) break;
        int ans=0;
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            ans^=x;
        }
        if(ans) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
