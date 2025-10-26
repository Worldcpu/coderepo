#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,ML=3;
int f[MN],n,a[MN],ans;
priority_queue<int> st[ML];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        f[i]=1;
        for(int j=0;j<ML;j++){
            if(((a[i]>>j)&1)&&st[j].size()){
                f[i]=max(f[i],st[j].top()+1);
            }
        }
        for(int j=0;j<ML;j++){
            if((a[i]>>j)&1){
                st[j].push(f[i]);
            }
        }
        ans=max(ans,f[i]);
    }
    cout<<ans;

    return 0;
}