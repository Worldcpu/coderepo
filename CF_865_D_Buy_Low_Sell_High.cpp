#include<bits/stdc++.h>
#include <cmath>
#define int long long
using namespace std;
int n;
priority_queue<int,vector<int>,greater<int>> q;

signed main(){
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        if(!q.empty()&&q.top()<k) ans+=k-q.top(),q.pop(),q.push(k); 
        q.push(k);
    }
    cout<<ans;
    return 0;
}
