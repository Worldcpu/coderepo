#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15,INF=1e18;
int n,X[MN],Y[MN],sumx[MN],sumy[MN],ans[MN],res;
pir a[MN],b[MN];




signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        X[i]=(x+y);
        Y[i]=(x-y);
        a[i]=pir(X[i],i);
        b[i]=pir(Y[i],i);
    }
    sort(a+1,a+1+n);
    sort(b+1,b+1+n);
    sort(X+1,X+1+n);
    sort(Y+1,Y+1+n);
    for(int i=1;i<=n;i++){
        sumx[i]=sumx[i-1]+X[i];
        sumy[i]=sumy[i-1]+Y[i];
    }
    for(int i=1;i<=n;i++){
        ans[a[i].second]+=i*a[i].first-sumx[i]+sumx[n]-sumx[i-1]-(n-i+1)*a[i].first;
        ans[b[i].second]+=i*b[i].first-sumy[i]+sumy[n]-sumy[i-1]-(n-i+1)*b[i].first;
    }
    res=INF;
    for(int i=1;i<=n;i++){
        res=min(res,ans[i]);
    }
    cout<<(res>>1);


    return 0;
}