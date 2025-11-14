#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,c[MN],ans,cnt;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        c[i+n]=c[i];
    }
    for(int i=1;i<=n;i++){
        ans+=c[i];
    }
    for(int i=1;i<=n;i++){
        if(c[i]!=0){
            ans+=cnt/2+cnt%2;
            cnt=0;
        }else cnt++;
    }
    ans+=cnt/2+cnt%2;
    cout<<ans;
    return 0;
}

