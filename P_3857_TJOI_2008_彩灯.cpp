#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MP=65;
int n,m;

struct xxj{
    int p[MP];
    
    void insert(int x){
        for(int i=63;i>=0;i--){
            if(!((x>>i)&1)) continue;
            if(!p[i]){
                p[i]=x;
                break;
            }
            x^=p[i];
        }
    }

}xj;

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x=0;
        string s;
        cin>>s;
        for(int i=0;i<s.size();i++){
            x|=(int)(s[i]=='O')<<i;
        }
        xj.insert(x);
    }
    int ans=0;
    for(int i=63;i>=0;i--){
        if(xj.p[i]) ans++;
    }
    cout<<(1<<ans)%2008;
    return 0;
}
