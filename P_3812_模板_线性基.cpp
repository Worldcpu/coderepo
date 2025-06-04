#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55;
int n;

struct xxj{
    int p[MN];

    void insert(int x){
        for(int i=52;i>=0;i--){
            if((x>>i)&1){
                if(!p[i]){
                    p[i]=x;
                    break;
                }
                x^=p[i];
            }
        }
    }

    int getmx(){
        int ans=0;
        for(int i=52;i>=0;i--){
            if((ans^p[i])>ans) ans^=p[i];
        }
        return ans;
    }

}xj;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        xj.insert(x);
    }
    cout<<xj.getmx();
    return 0;
}
