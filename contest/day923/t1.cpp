#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],b[MN],ans;
unordered_map<int,int> ump;


signed main(){
    freopen("no.in","r",stdin);
    freopen("no.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=30;i>=0;i--){
        int tmp=ans|(1<<i),flag=1;
        ump.clear();
        for(int j=1;j<=n;j++){
            ump[tmp&a[j]]++;
        }
        for(int j=1;j<=n;j++){
            int t=tmp&b[j];
            ump[(~t)&tmp]--;
        }
        for(auto p:ump){
            if(p.second!=0){
                flag=0;
                break;
            }
        }
        if(flag) ans=tmp;
    }
    cout<<ans;


    return 0;
}