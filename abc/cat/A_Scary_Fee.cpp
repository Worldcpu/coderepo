#include<bits/stdc++.h>
#define int long long
using namespace std;
double x,c;


signed main(){
    cin>>x>>c;
    int ans=0;
    for(int i=1;i<=1e5;i++){
        int cst=i*1000,nc=cst*c/1000;
        if(cst+nc<=x) ans=max(ans,cst);
    }
    cout<<ans;
    return 0;
}