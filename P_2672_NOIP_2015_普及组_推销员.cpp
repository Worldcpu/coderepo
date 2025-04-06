#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15;
int n,sum[MN],r[MN],l[MN];
struct node{
    int len,tir;
}a[MN];
bool cmp(node x,node y){
    return x.tir>y.tir;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].len;
    }
    for(int i=1;i<=n;i++){
        cin>>a[i].tir;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i].tir;
    }
    for(int i=1;i<=n;i++){
        l[i]=max(l[i-1],a[i].len*2);
    }
    for(int i=n;i>=1;i--){
        r[i]=max(r[i+1],a[i].len*2+a[i].tir);
    }
    for(int i=1;i<=n;i++){
        cout<<max(sum[i]+l[i],sum[i-1]+r[i])<<'\n';
    }
    return 0;
}