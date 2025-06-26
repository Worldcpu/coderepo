#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int T,n;

int main(){
    cin>>T;
    while(T--){
        cin>>n;
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
