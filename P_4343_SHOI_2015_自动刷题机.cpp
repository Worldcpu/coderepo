#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MN=5e5+15;
int n,ti;
template <typename type>
inline void read(type &x)
{
    x = 0;
    bool flag(0);
    char ch = getchar();
    while (!isdigit(ch))
        flag = ch == '-', ch = getchar();
    while (isdigit(ch))
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    flag ? x = -x : 0;
}
ll a[MN];
ll check(ll k){
    ll ret=0,cnt=0;
    for(int i=1;i<=n;i++){
        ret=max(ret+a[i],0ll);
        if(ret>=k){
            ret=0;
            cnt++;
        }
    }
    return cnt;
}
int main(){
    ios::sync_with_stdio(0);
    read(n);
    read(ti);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    ll l=1,r=1e18,ans1,ans2,mid,ret;
    while (l<=r)
    {
        mid=l+r>>1;
        ret=check(mid);
        if(ret<=ti){ 
            r=mid-1;
            if(ret==ti) ans1=mid;
        }
        else l=mid+1;
    }
    l=1,r=1e18;
    while (l<=r)
    {
        mid=l+r>>1;
        if(ret>=ti){ 
            l=mid+1;
            if(ret==ti) ans2=mid;
        }
        else r=mid-1;
    }
    if(ans1==1&&ans2==1||ans1>ans2||ans1==0||ans2==0){
        cout<<-1;
    }
    else cout<<ans1<<" "<<ans2;
    return 0;
}