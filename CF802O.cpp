#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15;
int a[MN],b[MN],K,n,sum,ans,cnt;

bool check(int k){
    priority_queue<pir,vector<pir>,greater<pir>> q;
    sum=cnt=0;
    for(int i=1;i<=n;i++){
        q.push(pir(a[i],0));
        pir tp=q.top();
        if(tp.first+b[i]+k<=0){
            sum+=tp.first+b[i]+k;
            if(!q.top().second) cnt++;
            q.pop();
            q.push({-b[i]-k,1});
        }
    }
    return cnt>=K;
}

signed main(){
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int l=-1e18,r=1e18;
    while(l<r){
        int mid=(l+r+1)>>1;
        if(check(mid)) l=mid;
        else r=mid-1;
    }   
    check(l);
    cout<<sum-K*l;
    return 0;
}