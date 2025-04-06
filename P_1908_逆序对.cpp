#include<iostream>
#include<algorithm>
using namespace std;
const int MN=5e5+15;
struct node
{
    int v,id;
};

int n,t[MN],rnk[MN];
node a[MN];
int lowbit(int x){
    return x & -x;
}
int ask(int x){
    int ans=0;
    while (x>0)
    {
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}
void add(int x,int k){
    while (x<=n)
    {
        t[x]+=k;
        x+=lowbit(x);
    }
}
bool cmp(node x,node y){
    if(x.v==y.v){
        return x.id<y.id;
    }
    return x.v<y.v;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].v;
        a[i].id=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        rnk[a[i].id]=i;
    }
    long long ans=0;
    for(int i=n;i>0;i--){
        add(rnk[i],1);
        ans+=ask(rnk[i]-1);
    }
    cout<<ans;
    return 0;
}