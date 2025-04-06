#include<iostream>
#define ll long long
using namespace std;
ll lowbit(ll x){
    return x & -x;
}
const int MN=1e5+15;
ll t1[MN],t2[MN],m,n,a[MN];
void add(ll *t,ll x,ll k){
    while (x<=n)
    {
        t[x]+=k;
        x+=lowbit(x);
    }
}
ll ask(ll *t,ll x){
    ll ans=0;
    while (x>0)
    {
        ans+=t[x];
        x-=lowbit(x);
    }
    return ans;
}
int main(){
    cin>>n>>m;
    for(ll i=1,pre=0;i<=n;i++){
        ll t;
        cin>>t;
        add(t1,i,t-pre);
        add(t2,i,(i-1)*(t-pre));
        pre=t;
    }
    while (m--)
    {
        ll q,l,r,k;
        cin>>q>>l>>r;
        if(q==1){
            cin>>k;
            add(t1,l,k);
            add(t1,r+1,-k);
            add(t2,l,k*(l-1));
            add(t2,r+1,-k*r);//-k*r=-k*(r+1-1)
        }else{
            cout<<r*ask(t1,r)-(l-1)*ask(t1,l-1)-ask(t2,r)+ask(t2,l-1)<<endl;
        }
    }
    
    return 0;
}