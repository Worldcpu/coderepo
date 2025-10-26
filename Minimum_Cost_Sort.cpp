#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],ans;

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]+=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x>0){
            ret+=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int query(int l,int r){
        if(l>r) return 0;
        return query(r)-query(l-1);
    }
}bit;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        int qwq=bit.query(a[i]+1,n);
        ans+=qwq*i-qwq*(qwq+1)/2;
        bit.modify(a[i],1);
    }
    cout<<ans;
    return 0;
}