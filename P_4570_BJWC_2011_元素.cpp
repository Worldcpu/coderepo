#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int mp=65,mn=1520;
int n;
pir a[mn];

struct xxj{
    int p[mp],ans=0;

    void insert(int x,int y){
        for(int i=63;i>=0;i--){
            if((x>>i)&1){
                if(!p[i]){
                    p[i]=x;
                    ans+=y;
                    break;
                }
                x^=p[i];
            }
        }
    }
}xj;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].second>>a[i].first;
    }
    sort(a+1,a+1+n);
    for(int i=n;i>=1;i--){
        xj.insert(a[i].second,a[i].first);
    }
    cout<<xj.ans;
    return 0;
}
