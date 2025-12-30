#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,q,a[MN],cf[MN],sum;


int half(int x){
	if(x>=0) return x/2;
	else if(x%2==0) return x/2;
	else return x/2-1;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cf[i]=a[i]-a[i-1];
    }   
    sum+=cf[1];
    for(int i=2;i<=n;i++){
        sum+=max(cf[i],0ll);
    }
    cout<<half(sum+1)<<'\n';
    cin>>q;
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        if(l!=1){
            sum-=max(cf[l],0ll);
            cf[l]+=x;
            sum+=max(cf[l],0ll);
        }else{
            sum-=cf[l];
            cf[l]+=x;
            sum+=cf[l];
        }
        if(r!=n){
            sum-=max(cf[r+1],0ll);
            cf[r+1]-=x;
            sum+=max(cf[r+1],0ll);
        }
        cout<<half(sum+1)<<'\n';
    }
    return 0;
}
