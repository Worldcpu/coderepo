#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,a[MN],p[MN],ans;

bool cmp(int x,int y){
    return x>y;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        int x=a[i];
        for(int j=30;j>=0;j--){
            if((x>>j)&1){
                if(!p[j]){
                    p[j]=x;
                    break;
                }else x^=p[j];
            }
        }
        if(!x){
            ans+=a[i];
        }
    }
    cout<<ans;

    return 0;
}