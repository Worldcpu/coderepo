#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
string s;

signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    freopen("palin.in","r",stdin);
    freopen("palin.out","w",stdout);
    cin>>n>>s; s=" "+s;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(s[i]!=s[j]) ans++;
            else break;
        }
    }
    cout<<n*(n-1)/2-ans;
}
