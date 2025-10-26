#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15;
int n,p[MN],c[MN],f[MN],tot,ans;
vector<int> col[MN];

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        cin>>c[i];
        col[c[i]].push_back(p[i]);
    }
    for(int i=1;i<=n;i++){
        tot=0;
        for(auto p:col[i]){
            if(p>f[tot]) f[++tot]=p;
            else{
                int tmp=lower_bound(f+1,f+1+tot,p)-f;
                f[tmp]=p;
            }
        }
        ans+=i*(col[i].size()-tot);
    }
    cout<<ans;
    

    return 0;
}