#include<bits/stdc++.h>
using namespace std;
const int MN=1e5+15;
struct node
{
    int x,y;
}a[MN];
int t[MN],n;
bool cmp(node x,node y){
    if(x.x==y.x) return x.y<y.y;
    return x.x<y.x;
}
int lowbit(int x){
    return x&(-x);
}
int add(int x,int k){
    while (x<=n)
    {
        t[x]+=k;
        x+=lowbit(x);
    }
}
int query(int x){
    int ans=0;
    while (x)
    {
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].x
    }
    sort(a+1,a+1+n,cmp);
    return 0;
}