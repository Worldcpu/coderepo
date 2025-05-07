#include<iostream>
#include<queue>
#include<algorithm>
#define int long long
using namespace std;
struct work
{
    int stop,price;
};
int n;
bool cmp(work x,work y){
    return x.stop<y.stop;
}
priority_queue<int,vector<int>,greater<int>> q;
void solve(){ 
    while(!q.empty()) q.pop();
    work a[n+1];
    for(int i=1;i<=n;i++){
        cin>>a[i].price>>a[i].stop;
    }
    sort(a+1,a+1+n,cmp);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(a[i].stop<=q.size()){
            if(a[i].price>q.top()){
                ans-=q.top();
                q.pop();
                q.push(a[i].price);
                ans+=a[i].price;
            }
        }else{
            q.push(a[i].price);
            ans+=a[i].price;
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    while(cin>>n){
        solve();
    }
    return 0;
}