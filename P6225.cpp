#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,q,a[MN];

struct BIT{
    int t[MN];

    int lowbit(int x){
        return x&-x;
    }

    void modify(int x,int k){
        while(x<MN){
            t[x]^=k;
            x+=lowbit(x);
        }
    }

    int query(int x){
        int ret=0;
        while(x>0){
            ret^=t[x];
            x-=lowbit(x);
        }
        return ret;
    }

    int query(int l,int r){
        return query(r)^query(l-1);
    }
}bit[2]; // bit[0]->1 is oo bit[1]-> 1 is ee


int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        bit[i&1].modify(i,a[i]);
    }
    while(q--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            bit[x&1].modify(x,a[x]);
            a[x]=y;
            bit[x&1].modify(x,y);
        }else{
            if((y-x+1)%2==0) cout<<0<<'\n';
            else cout<<bit[x&1].query(x,y)<<'\n';
        }
    }
    return 0;
}