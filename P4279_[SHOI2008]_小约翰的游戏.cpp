#include<bits/stdc++.h>
using namespace std;
int T,n;

void solve(){
    cin>>n;
    int ans=0;
    bool flag=0;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        ans^=x;
        if(x>1) flag=1;
    }
    if(!flag&&!ans) cout<<"John\n";
    else if(flag&&ans) cout<<"John\n";
    else cout<<"Brother\n";
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
