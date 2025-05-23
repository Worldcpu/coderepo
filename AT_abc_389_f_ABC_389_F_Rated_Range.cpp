#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
struct Query{
    int l,r,id;
}qry[MN];
int n,q,ans[MN];
pir a[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void update(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    void chg(int L,int R){
        int l=1,r=L,ans1=1,ans2=1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(mid+query(mid)>=L) r=mid-1,ans1=mid;
            else l=mid+1;
        }
        l=1,r=R;
        while(l<=r){
            int mid=(l+r)>>1;
            if(mid+query(mid)<=R) l=mid+1,ans2=mid;
            else r=mid-1;
        }
        update(ans1,1);
        update(ans2+1,-1);
    }

}bit;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].first>>a[i].second;
        bit.chg(a[i].first,a[i].second);
    }
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        cout<<x+bit.query(x)<<'\n';
    }
    return 0;
}
